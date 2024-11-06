//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef REQUESTMETHOD_H_
#define REQUESTMETHOD_H_

namespace webloom {

enum class RequestMethod {
    Get,
    Post,
    Put,
    Patch,
    Delete,
    Head,
    Options
};

}   // namespace webloom

#endif  // REQUESTMETHOD_H_
