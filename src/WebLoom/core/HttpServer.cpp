//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "HttpServer.h"
#include "core/ThreadPool.h"
#include "Response.h"
#include "core/HttpStatus.h"
#include "HttpContentType.h"
#include "RouteHandler.h"

namespace webloom::core {

constexpr unsigned int MAX_REQUEST_BUFFER_SIZE = 30000;

HttpServer::HttpServer(Logger* logger,
                       WebLoomSettings *settings,
                       core::FileServer *fileServer)
    : ServerBase(logger, settings, fileServer) {
}

void HttpServer::ServerLoop() {
    socklen_t addrLength = sizeof(socket_address_);

    SOCKET newSocket = accept(server_socket_,
                              (struct sockaddr*)&socket_address_,
                              &addrLength);

    if (newSocket == INVALID_SOCKET) {
        closesocket(server_socket_);
        CleanupSocketSystem();
        throw std::runtime_error("Accept failed");
    }

    logger_->LogDebug("Assigning connection to thread pool...");
    threadpool_->enqueue(std::bind(
                         &HttpServer::HandleClientRequest,
                         this,
                         std::move(newSocket)));
}

void HttpServer::HandleClientRequest(SOCKET clientSocket) {
    std::vector<char> buffer(MAX_REQUEST_BUFFER_SIZE, 0);
    int amountRead = recv(clientSocket,
        buffer.data(),
        MAX_REQUEST_BUFFER_SIZE,
        0);

    if (amountRead > 0) {
        std::string request_str(buffer.data());
        Request *request = ProcessRequest(buffer);

        logger_->LogDebug("Request Information:");
        logger_->LogDebug("=> Method          : %d",
            request->Method());
        logger_->LogDebug("=> Path            : %s",
            request->Path().c_str());
        logger_->LogDebug("=> HTTP Version    : %d",
            request->HttpRequestVersion());
        logger_->LogDebug("=> Remote Host     : %s",
            request->RemoteHost().c_str());
        logger_->LogDebug("=> Client Platform : %d",
            static_cast<int>(request->ClientPlatform()));
        logger_->LogDebug("=> User-Agent      : %s",
            request->UserAgent().c_str());

        // Print the header key/values
        logger_->LogDebug("|= Header key/value pairs:");
        auto keys = request->Headers().AllKeys();
        for (const auto& key : keys) {
            logger_->LogDebug("    %s : %s",
                key.c_str(),
                request->Headers().Get(key)->c_str());
        }

        auto staticWebDir = settings_->StaticWebsiteDir();
        auto route = staticWebDir + request->Path();

        std::optional<Response *> response = nullptr;

        if (RouteHandler::Instance().IsValidRoute(request->Path(),
                                                  request->Method())) {
            response = RouteHandler::Instance().HandleRequest(request->Path(),
                                                              request->Method(),
                                                              request);
        } else {
            auto httpStatus = core::HttpStatus::OK;
            auto contentType = HttpContentType::TextPlain;
            std::string body = "";

            // Remove any leading '/' from the route as
            if (!route.empty() && route.front() == '/') {
                route.erase(0, 1);
            }

            auto servedFileDetails = file_server_->ServeFile(route);
            if (!servedFileDetails) {
                body = "<html><body><h1>404 Page Not Found</h1></body></html>";
                httpStatus = core::HttpStatus::NotFound;
            } else {
                body = servedFileDetails->contents;
                contentType = servedFileDetails->contentType;
            }

            response = new Response(httpStatus,
                                    body,
                                    contentType);
        }

        SendResponse(clientSocket, response.value());
        closesocket(clientSocket);
    }
}

std::string HttpServer::GenerateResponseHeader(Response *response) {
    size_t bodyLength = response->Body().size();
    int statusCode = static_cast<int>(response->StatusCode());

    std::string headerStr =
        "HTTP/1.1 " + std::to_string(statusCode) + " " +
        HttpStatusString(response->StatusCode()) + "\r\n"
        "Content-Type: " +
        HttpContentTypeString(response->ContentType()) + "\r\n"
        "Content-Length: " + std::to_string(bodyLength) + "\r\n"
        "\r\n";

    return headerStr;
}

int HttpServer::SendResponse(SOCKET socket, Response *response) {
    std::string responseStr = GenerateResponseHeader(response) +
                              response->Body();

    int bytesSent = send(socket,
                         responseStr.c_str(),
                         static_cast<int>(responseStr.length()),
                         0);
    return bytesSent;
}

}   // namespace webloom::core
