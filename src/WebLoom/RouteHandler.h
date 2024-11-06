//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef ROUTEHANDLER_H_
#define ROUTEHANDLER_H_
#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "Request.h"
#include "RequestMethod.h"
#include "Response.h"

namespace webloom {

using RequestMethodList = const std::vector<RequestMethod>;
using RouteHandlerFunction = std::function<Response *(Request *)>;

struct RouteEntry {
    const RequestMethodList methods;
    RouteHandlerFunction handler;
};

class RouteHandler {
 public:
    static RouteHandler& Instance() {
        static RouteHandler instance;
        return instance;
    }

    void AddRoute(const std::string& route,
                  const RequestMethodList& methods,
                  RouteHandlerFunction handler);

    std::optional<webloom::Response*> HandleRequest(const std::string& route,
                                                    const RequestMethod method,
                                                    Request *request);

    bool IsValidRoute(const std::string& route, RequestMethod method);

 private:
    std::unordered_map<std::string, RouteEntry> routes_;
    RouteHandler() = default;   // Private constructor for singleton pattern
};

}   // namespace webloom

// Macro to register routes with a user-defined handler function
#define WEBLOOM_ROUTE(path, methods, handler) \
    do { \
        (void)(webloom::RouteHandler::Instance().AddRoute( \
            path, \
            methods, \
            [this](webloom::Request *req) { return this->handler(req); })); \
    } while (0)
#endif  // ROUTEHANDLER_H_
