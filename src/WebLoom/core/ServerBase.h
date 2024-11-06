//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef CORE_SERVERBASE_H_
#define CORE_SERVERBASE_H_
#include <atomic>
#include <string>
#include <vector>
#include "IServer.h"
#include "Logger.h"
#include "Request.h"
#include "SocketDefinitions.h"
#include "WebLoomSettings.h"
#include "core/FileServer.h"

namespace webloom::core {

class ThreadPool;

class ServerBase : public IServer {
 public:
    ServerBase(Logger *logger,
               WebLoomSettings *settings,
               core::FileServer *fileServer);

    ~ServerBase();

    void Run();

    void RequestShutdown();

 protected:
    Logger *logger_;
    std::atomic<bool> shutdown_requested_;
    WebLoomSettings *settings_;
    core::FileServer *file_server_;
    SOCKET server_socket_;
    sockaddr_in socket_address_;
    ThreadPool* threadpool_;

    std::string CleanHeaderString(std::string src);

    bool InitialiseSocketSystem();

    Request *ProcessRequest(const std::vector<char>& buffer);

    void ParseHeaders(const std::string& headers, Request* request);

    HttpVersion ParseHttpVersion(std::string version);

    void CleanupSocketSystem();

    RequestMethod ParseRequestType(std::string method);

    void SplitRequestIntoHeadersAndBody(const std::string& request,
                                        std::string* headers,
                                        std::string* body);

    UserAgentClientPlatform ParseUserAgentClientPlatform(std::string platform);
};

}   // namespace webloom::core

#endif  // CORE_SERVERBASE_H_
