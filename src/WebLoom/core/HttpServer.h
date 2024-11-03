//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef CORE_HTTPSERVER_H_
#define CORE_HTTPSERVER_H_
#include <string>
#include "Response.h"
#include "ServerBase.h"

namespace webloom::core {

class HttpServer : public ServerBase {
 public:
     HttpServer(Logger *logger,
                WebLoomSettings *settings,
                core::FileServer *fileServer);

 private:
    void ServerLoop();

    void HandleClientRequest(SOCKET clientSocket);

    std::string GenerateResponseHeader(Response *response);

    int SendResponse(SOCKET socket, Response *response);
};

}   // namespace webloom::core

#endif  // CORE_HTTPSERVER_H_
