//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <stdexcept>
#include "Header.h"

namespace webloom {

Header::Header() {
}

void Header::Add(std::string key, std::string value) {
    if (header_values_.find(key) != header_values_.end()) {
        throw std::runtime_error("Duplicate entry");
    }

    header_values_[key] = { key, value };
}

const std::string *Header::Get(std::string key) {
    auto it = header_values_.find(key);

    if (it != header_values_.end()) {
        return &it->second.value;
    }

    return nullptr;
}

std::vector<std::string> Header::AllKeys() {
    std::vector<std::string> keys;

    // Iterate through the map and collect keys
    for (const auto& pair : header_values_) {
        keys.push_back(pair.first);
    }

    return keys;
}

}   // namespace webloom
