//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef TEMPLATER_H_
#define TEMPLATER_H_
#include <map>
#include <string>
#include "core/Logger.h"
#include "core/FileServer.h"
#include "Response.h"
#include "WebLoomSettings.h"

namespace webloom {

using TemplateArguments = std::map<std::string, std::string>;

class Templater {
 public:
    static Templater& Instance() {
        static Templater instance;
        return instance;
    }

    void Initialise(core::Logger* logger,
                    WebLoomSettings* settings,
                    core::FileServer* fileserver);

    Response *RenderTemplate(std::string filename,
                             TemplateArguments args = TemplateArguments());

 private:
     class Implementation;
     Implementation* impl_;
     core::Logger* logger_;
     WebLoomSettings* settings_;
     core::FileServer* fileserver_;

    Templater() = default;   // Private constructor for singleton pattern
};

}   // namespace webloom

#endif  // TEMPLATER_H_
