//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef WEBLOOMEXCEPTIONS_H_
#define WEBLOOMEXCEPTIONS_H_
#include <stdexcept>
#include <string>

namespace webloom {

class WebLoomBaseException : public std::exception {
 public:
    explicit WebLoomBaseException(const std::string& message)
             : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

 protected:
    std::string message_;
};

class TemplateNotFound : public WebLoomBaseException {
 public:
    explicit TemplateNotFound(const std::string& message)
        : WebLoomBaseException(message) {}
};

class TemplateRenderFailed : public WebLoomBaseException {
 public:
    explicit TemplateRenderFailed(const std::string& message)
        : WebLoomBaseException(message) {}
};

}   // namespace webloom

#endif  // WEBLOOMEXCEPTIONS_H_
