//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <algorithm>
#include <stdexcept>
#include "RouteHandler.h"

namespace webloom {

/**
 * @brief Adds a new route entry to the route handler.
 *
 * This function registers a route by associating it with a list of supported
 * HTTP methods and a handler function. The handler function will be invoked
 * to process requests that match the specified route and method.
 *
 * @param route The route path as a string (e.g., "/api/resource").
 * @param methods A list of supported HTTP methods for the route (e.g., GET,
 *                POST).
 * @param handler A function to handle requests for the route. This function
*                 should match the signature defined by RouteHandlerFunction.
*/
void RouteHandler::AddRoute(const std::string& route,
                            const RequestMethodList& methods,
                            RouteHandlerFunction handler) {
    routes_.emplace(route, RouteEntry{ methods, handler });
}

/**
 * @brief Handles an incoming request for a specified route and method.
 *
 * This function looks up a given route in the internal route map, checks if
 * the request method is supported for that route, and if so, invokes the
 * associated route handler function. If the route or method does not exist,
 * it returns an empty optional.
 *
 * @param route The requested route as a string.
 * @param method The HTTP request method (e.g., GET, POST).
 * @param request A pointer to the Request object containing the request
                  details.
 * @return std::optional<webloom::Response*>
 *         - A pointer to a Response object if the route and method are found
 *           and handled.
 *         - std::nullopt if the route or method is not found.
 */
std::optional<webloom::Response *> RouteHandler::HandleRequest(
    const std::string& route, const RequestMethod method, Request *request) {
    auto it = routes_.find(route);
    if (it != routes_.end()) {
        const auto& entry = it->second;

        if (std::find(entry.methods.begin(),
                      entry.methods.end(),
                      method) != entry.methods.end()) {
            // Call the handler and return the response.
            return entry.handler(request);
        }
    }

    // Route or method not found
    return std::nullopt;
}

bool RouteHandler::IsValidRoute(const std::string& route,
                                RequestMethod method) {
    auto it = routes_.find(route);
    if (it != routes_.end()) {
        const auto& entry = it->second;

        if (std::find(entry.methods.begin(),
                      entry.methods.end(),
                      method) != entry.methods.end()) {
            return true;
        }
    }

    return false;
}

}   // namespace webloom
