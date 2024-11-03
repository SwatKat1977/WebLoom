//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef RESPONSE_H_
#define RESPONSE_H_
#include <string>
#include "Header.h"
#include "HttpContentType.h"
#include "core/HttpStatus.h"

enum class HttpStatus;

namespace webloom {

class Response {
 public:
    Response(core::HttpStatus statusCode,
             const std::string body,
             core::HttpContentType contentType);

    core::HttpStatus StatusCode() const { return status_code_; }

    const Header &ResponseHeader() { return header_; }
    void ResponseHeader(const Header& header ) { header_ = header; }

    const std::string &Body() { return body_; }

    core::HttpContentType ContentType() const { return content_type_; }

 private:
    core::HttpStatus status_code_;
    Header header_;
    std::string body_;
    core::HttpContentType content_type_;
};

}   // namespace webloom

#endif  // RESPONSE_H_
