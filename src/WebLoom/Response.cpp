//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include "Response.h"

namespace webloom {

Response::Response(core::HttpStatus statusCode,
                   const std::string body,
                   core::HttpContentType contentType)
         : status_code_(statusCode), header_(Header()), body_(body),
           content_type_(contentType) {
}

}   // namespace webloom
