//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef REQUEST_H_
#define REQUEST_H_
#include <string>
#include "RequestMethod.h"
#include "Header.h"

namespace webloom {

enum class RequestMethod;

enum class HttpVersion {
    // HTTP / 1.0: Introduced headers, status codes, and more methods, but each
    // request required a new connection.
    HTTP_1_0,

    // HTTP / 1.1 : Introduced persistent connections, chunked transfers, and
    // is the most widely used version.
    HTTP_1_1,

    // HTTP / 2 : Introduced a binary protocol, multiplexing, header
    // compression, and server push for better performance.
    HTTP_2_0
};

/**
 * @brief Represents the client platform of a user's device based on the
 * User-Agent string.
 *
 * This enum class defines the different types of client platforms that can be
 * identified from a User-Agent string. It categorizes various operating
 * systems commonly used on desktop and mobile devices.
 */
enum class UserAgentClientPlatform {
    Windows,   ///< Microsoft Windows operating system
    macOS,     ///< Apple macOS operating system
    Linux,     ///< Linux operating system
    Android,   ///< Google Android mobile operating system
    iOS,       ///< Apple iOS mobile operating system
    ChromeOS,  ///< Google ChromeOS operating system
    Unknown    ///< Unknown or unsupported platform
};

class Request {
 public:
    Request(RequestMethod method, HttpVersion httpVersion, std::string path);

    void UserAgent(std::string agent) { user_agent_ = agent; }
    std::string UserAgent() { return user_agent_; }

    HttpVersion HttpRequestVersion() { return http_version_; }

    RequestMethod Method() { return request_method_; }

    std::string Path() { return path_;  }

    void RemoteHost(std::string host) { host_ = host; }
    std::string RemoteHost() { return host_; }

    void ClientPlatform(UserAgentClientPlatform platform) {
        client_platform_ = platform;
    }
    UserAgentClientPlatform ClientPlatform() { return client_platform_; }

    void AddHeaders(const Header& header) { header_ = header; }

    Header Headers() { return header_; }

 private:
    Header header_;
    std::string host_;
    HttpVersion http_version_;
    std::string path_;
    RequestMethod request_method_;
    std::string user_agent_;
    UserAgentClientPlatform client_platform_;
};

}   // namespace webloom

#endif  // REQUEST_H_

