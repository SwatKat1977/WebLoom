//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <utility>
#include "Request.h"

namespace webloom {

Request::Request(RequestMethod method, HttpVersion httpVersion,
                 std::string path) : http_version_(httpVersion),
                 path_(std::move(path)), request_method_(method),
                 client_platform_(UserAgentClientPlatform::Unknown) {
}

}   // namespace webloom
