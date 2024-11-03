//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef HEADER_H_
#define HEADER_H_
#include <string>
#include <map>
#include <vector>
#include "RequestMethod.h"

namespace webloom {

struct HeaderKeyValuePair {
    std::string key;
    std::string value;
};

class Header{
 public:
    Header();

    void Add(std::string key, std::string value);

    const std::string *Get(std::string key);

    std::vector<std::string> AllKeys();

 private:
    std::map<std::string, HeaderKeyValuePair> header_values_;
};

}   // namespace webloom

#endif  // HEADER_H_
