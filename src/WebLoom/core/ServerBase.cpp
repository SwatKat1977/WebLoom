//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>
#include "ServerBase.h"
#include "core/ThreadPool.h"
#include "Header.h"
#include "Request.h"

namespace webloom::core {

// User-Agent Client Platforms

constexpr const char* USERAGENTCLIENTPLATFORM_WINDOWS = "Windows";
constexpr const char* USERAGENTCLIENTPLATFORM_MACOS = "macOS";
constexpr const char* USERAGENTCLIENTPLATFORM_LINUX = "Linux";
constexpr const char* USERAGENTCLIENTPLATFORM_ANDROID = "Android";
constexpr const char* USERAGENTCLIENTPLATFORM_IOS = "iOS";
constexpr const char* USERAGENTCLIENTPLATFORM_CHROMEOS = "ChromeOS";
constexpr const char* USERAGENTCLIENTPLATFORM_UNKNOWN = "Unknown";

// HTTP Version

constexpr const char* HTTP_VERSION_1_0 = "HTTP/1.0";
constexpr const char* HTTP_VERSION_1_1 = "HTTP/1.1";
constexpr const char* HTTP_VERSION_2_0 = "HTTP/2.0";

// HTTP Method types

constexpr const char* METHOD_TYPE_GET = "GET";
constexpr const char* METHOD_TYPE_POST = "POST";
constexpr const char* METHOD_TYPE_PUT = "PUT";
constexpr const char* METHOD_TYPE_PATCH = "PATCH";
constexpr const char* METHOD_TYPE_DELETE = "DELETE";
constexpr const char* METHOD_TYPE_HEAD = "HEAD";
constexpr const char* METHOD_TYPE_OPTIONS = "OPTIONS";

constexpr const char* HEADER_KEY_HOST = "Host";
constexpr const char* HEADER_KEY_USER_AGENT = "User-Agent";
constexpr const char* HEADER_KEY_CLIENT_PLATFORM = "sec-ch-ua-platform";

constexpr unsigned int MAX_THREADS = 4;

ServerBase::ServerBase(Logger* logger,
                       WebLoomSettings *settings,
                       core::FileServer *fileServer)
          : logger_(logger), shutdown_requested_(false),
            server_socket_(INVALID_SOCKET) {
    settings_ = settings;
    file_server_ = std::move(fileServer);

    // Initialize the socket_address_ structure to zero out the structure.
    memset (&socket_address_, 0, sizeof (socket_address_));

    if (!InitialiseSocketSystem()) {
        throw std::runtime_error("Socket initialisation failed!");
    }

    threadpool_ = new ThreadPool(MAX_THREADS);
}

ServerBase::~ServerBase() {
    CleanupSocketSystem();
    printf("ServerBase::~ServerBase()\n");
}

void ServerBase::Run() {
    // Create the server socket.
    if ((server_socket_ = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        CleanupSocketSystem();
        throw std::runtime_error("Failed to create server socket");
    }

    // Bind to a port and IP address
    socket_address_.sin_family = AF_INET;
    socket_address_.sin_addr.s_addr = INADDR_ANY;
    socket_address_.sin_port = htons(settings_->ServerNetworkPort());

    if (bind(server_socket_, (struct sockaddr*)&socket_address_,
             sizeof(socket_address_)) == SOCKET_ERROR) {
        closesocket(server_socket_);
        CleanupSocketSystem();
        throw std::runtime_error("Failed to bind server socket");
    }

    // Start listening for connections
    if (listen(server_socket_, 3) == SOCKET_ERROR) {
        int errorCode = 0;
#if (WEBLOOM_PLATFORM == WEBLOOM_PLATFORM_WINDOWS_MSVC)
        errorCode = WSAGetLastError();
#elif (WEBLOOM_PLATFORM == WEBLOOM_PLATFORM_LINUX)
        errorCode = errno;
#endif
        closesocket(server_socket_);
        CleanupSocketSystem();
        throw std::runtime_error("Server socket listen failed with error code: "
            + errorCode);
    }

    logger_->LogInfo("Server is listening on port %d",
                     settings_->ServerNetworkPort());

    while (!shutdown_requested_) {
        ServerLoop();
    }

    // Close the server socket
    closesocket(server_socket_);
    CleanupSocketSystem();
}

void ServerBase::RequestShutdown() {
    shutdown_requested_ = true;
}

Request *ServerBase::ProcessRequest(const std::vector<char>& buffer) {
    std::string request_str(buffer.data());

    // Split the request into headers and body
    std::string headers;
    std::string body;
    SplitRequestIntoHeadersAndBody(request_str, &headers, &body);

    // Split request into lines (delimited by \r\n)
    std::istringstream request_stream(buffer.data());
    std::string line;

    std::string method;
    std::string path;
    std::string http_version;
    request_stream >> method >> path >> http_version;

    // Default to index.html if root is requested
    if (path == "/") {
        logger_->LogDebug("Path is ROOT");
        path = "/index.html";
    }

    auto requestTypeEnum = ParseRequestType(method);
    auto httpVersionEnum = ParseHttpVersion(http_version);
    Request* request = new Request(requestTypeEnum, httpVersionEnum, path);

    ParseHeaders(headers, request);

    return request;
}

/**
 * @brief Initializes the socket system for Windows platforms.
 *
 * This function initializes the Winsock library required for network
 * communication on Windows-based platforms. It checks if the platform
 * is either `WEBLOOM_PLATFORM_WINDOWS_CORE` or `WEBLOOM_PLATFORM_WINDOWS_MSVC`
 * and attempts to initialize Winsock using the `WSAStartup` function.
 *
 * If the platform is not Windows, the function returns `true` by default,
 * indicating that the socket system is considered initialized.
 *
 * @note This function is only compiled and executed on Windows platforms
 * where Winsock initialization is required. On other platforms, this
 * function assumes that the socket system is already initialized.
 *
 * @return `true` if the Winsock initialization (`WSAStartup`) succeeds
 *         or if the platform is not Windows; otherwise, returns `false`
 *         if the initialization fails on Windows.
 *
 * @remarks The `MAKEWORD(2, 2)` macro specifies version 2.2 of the Winsock API.
 *          The `WSAStartup` function returns `0` on success, so the function
 *          returns `true` when the result is `0`; otherwise, it returns `false`.
 *
 * Example usage:
 * @code
 * Context context;
 * if (context.InitialiseSocketSystem()) {
 *     // Socket system initialized successfully.
 * } else {
 *     // Failed to initialize socket system.
 * }
 * @endcode
 */
bool ServerBase::InitialiseSocketSystem() {
#if WEBLOOM_PLATFORM == WEBLOOM_PLATFORM_WINDOWS_CORE || \
    WEBLOOM_PLATFORM == WEBLOOM_PLATFORM_WINDOWS_MSVC
    int result;
    WSADATA wsaData;

    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    return (result != 0) ? false : true;
#else
    return true;
#endif
}

void ServerBase::CleanupSocketSystem() {
#if (WEBLOOM_PLATFORM == WEBLOOM_PLATFORM_WINDOWS_MSVC)
    WSACleanup();
#endif
}

/**
 * @brief Cleans a string by removing unnecessary characters like carriage
   returns and quotes.
 *
 * This function takes a string as input and performs the following operations:
 * - Removes a trailing carriage return character (`\r`) if present.
 * - Removes leading and trailing double quote characters (`"`).
 *
 * @param src The input string that needs to be cleaned.
 * @return A cleaned version of the input string without carriage returns or surrounding quotes.
 */
std::string ServerBase::CleanHeaderString(std::string src) {
    std::string dest = src;

    // Remove carriage return
    if (!dest.empty() && dest.back() == '\r') {
        dest.erase(dest.size() - 1);
    }

    // Remove leading quote
    if (!dest.empty() && dest.front() == '\"') {
        dest.erase(0, 1);
    }

    // Remove trailing quote
    if (!dest.empty() && dest.back() == '\"') {
        dest.erase(dest.size() - 1);
    }

    return dest;
}

/**
 * @brief Parses the HTTP headers from the input string and updates the request
 *        object accordingly.
 *
 * This function reads a string containing HTTP headers, parses each header
 * line, and updates the Request object with relevant information such as the
 * remote host, user-agent, and client platform. Unrecognized headers are
 * stored in the webloom::Header object, which is then added to the request.
 *
 * @param headers String containing HTTP headers in key-value format.
 * @param request Reference to the Request object to be updated with parsed
 *        headers.
 */
void ServerBase::ParseHeaders(const std::string& headers,
    Request* request) {
    logger_->LogDebug("Entering RequestProcessor::ParseHeaders()");

    webloom::Header header;
    std::istringstream stream(headers);
    std::string line;
    std::string header_key;
    std::string header_value;

    while (std::getline(stream, line) && line != "\r") {
        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            header_key = line.substr(0, colon_pos);
            header_value = line.substr(colon_pos + 1);

            // Trim spaces from the header value
            header_value.erase(0, header_value.find_first_not_of(' '));
            header_value.erase(header_value.find_last_not_of(' ') + 1);

            if (header_key == HEADER_KEY_HOST) {
                request->RemoteHost(header_value);
            } else if (header_key == HEADER_KEY_USER_AGENT) {
                request->UserAgent(header_value);
            } else if (header_key == HEADER_KEY_CLIENT_PLATFORM) {
                auto platform = ParseUserAgentClientPlatform(header_value);
                request->ClientPlatform(platform);
            } else {
                header.Add(header_key, header_value);
            }
        }
    }

    request->AddHeaders(header);
}

/**
 * @brief Parses an HTTP version string and returns the corresponding enum
 *        value.
 *
 * This function takes an HTTP version string as input and returns the
 * corresponding
 * `HttpVersion` enum value. The function recognizes the following HTTP
 * versions:
 * - `HTTP/1.0`: Returns `HttpVersion::HTTP_1_0`.
 * - `HTTP/1.1`: Returns `HttpVersion::HTTP_1_1`.
 * - `HTTP/2.0`: Returns `HttpVersion::HTTP_2_0`.
 *
 * If the input string does not match any of the known HTTP versions, the
 * function throws an `std::invalid_argument` exception.
 *
 * @param version A string representing the HTTP version (e.g., "HTTP/1.0").
 * @return The corresponding `HttpVersion` enum value.
 * @throws std::invalid_argument if the input does not match any valid HTTP
 *         version.
 */
HttpVersion ServerBase::ParseHttpVersion(std::string version) {
    if (version == HTTP_VERSION_1_0) {
        return HttpVersion::HTTP_1_0;
    } else if (version == HTTP_VERSION_1_1) {
        return HttpVersion::HTTP_1_1;
    } else if (version == HTTP_VERSION_2_0) {
        return HttpVersion::HTTP_2_0;
    }

    throw std::invalid_argument("Invalid HTTP version");
}

/**
 * @brief Parses a request method string and returns the corresponding enum
 * value.
 *
 * This function takes a string representing an HTTP request method and returns
 * the corresponding `RequestMethod` enum value. It supports the following
 * methods:
 * - GET
 * - POST
 * - PUT
 * - PATCH
 * - DELETE
 * - HEAD
 * - OPTIONS
 *
 * If the input string does not match any known method, an
 * `std::invalid_argument` exception is thrown.
 *
 * @param method A string representing the HTTP request method.
 * @return The corresponding `RequestMethod` enum value.
 * @throws std::invalid_argument if the method is invalid.
 */
RequestMethod ServerBase::ParseRequestType(std::string method) {
    if (method == METHOD_TYPE_GET) {
        return RequestMethod::Get;
    } else if (method == METHOD_TYPE_POST) {
        return RequestMethod::Post;
    } else if (method == METHOD_TYPE_PUT) {
        return RequestMethod::Put;
    } else if (method == METHOD_TYPE_PATCH) {
        return RequestMethod::Patch;
    } else if (method == METHOD_TYPE_DELETE) {
        return RequestMethod::Delete;
    } else if (method == METHOD_TYPE_HEAD) {
        return RequestMethod::Head;
    } else if (method == METHOD_TYPE_OPTIONS) {
        return RequestMethod::Options;
    }

    throw std::invalid_argument("Invalid method type");
}

/**
 * @brief Parses a platform string from the User-Agent and returns the
 * appropriate enum value.
 *
 * This function takes a platform string from the User-Agent header, cleans it,
 * and returns the corresponding `UserAgentClientPlatform` enum value. It
 * recognizes the following platforms:
 * - Windows
 * - macOS
 * - Linux
 * - Android
 * - iOS
 * - ChromeOS
 * - Unknown
 *
 * If the input string does not match any known platform, an
 * `std::invalid_argument` exception is thrown.
 *
 * @param platform A string representing the User-Agent platform.
 * @return The corresponding `UserAgentClientPlatform` enum value.
 * @throws std::invalid_argument if the platform is invalid.
 */
UserAgentClientPlatform ServerBase::ParseUserAgentClientPlatform(
    std::string platform) {
    platform = CleanHeaderString(platform);

    if (platform == USERAGENTCLIENTPLATFORM_WINDOWS) {
        return UserAgentClientPlatform::Windows;
    } else if (platform == USERAGENTCLIENTPLATFORM_MACOS) {
        return UserAgentClientPlatform::macOS;
    } else if (platform == USERAGENTCLIENTPLATFORM_LINUX) {
        return UserAgentClientPlatform::Linux;
    } else if (platform == USERAGENTCLIENTPLATFORM_ANDROID) {
        return UserAgentClientPlatform::Android;
    } else if (platform == USERAGENTCLIENTPLATFORM_IOS) {
        return UserAgentClientPlatform::iOS;
    } else if (platform == USERAGENTCLIENTPLATFORM_CHROMEOS) {
        return UserAgentClientPlatform::ChromeOS;
    } else if (platform == USERAGENTCLIENTPLATFORM_UNKNOWN) {
        return UserAgentClientPlatform::Unknown;
    }

    throw std::invalid_argument("Invalid Agent Client platform");
}

void ServerBase::SplitRequestIntoHeadersAndBody(
    const std::string& request,
    std::string* headers,
    std::string* body) {
    // Find the position of the blank line (\r\n\r\n)
    size_t pos = request.find("\r\n\r\n");

    // If the blank line is not found, return only headers (i.e., no body)
    if (pos == std::string::npos) {
        *headers = request;
        *body = "";
        return;
    }

    // Split the request into headers and body
    *headers = request.substr(0, pos);
    *body = request.substr(pos + 4);  // Body starts after \r\n\r\n
}

}   // namespace webloom::core
