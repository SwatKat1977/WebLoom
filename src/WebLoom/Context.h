//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef CONTEXT_H_
#define CONTEXT_H_
#include <memory>
#include <string>
#include "core/Logger.h"
#include "core/IServer.h"
#include "WebLoomSettings.h"
#include "core/FileServer.h"

namespace webloom {

const core::LoggerSettings DefaultLoggerSettings;

class Context {
 public:
     explicit Context(std::string contextName,
                      WebLoomSettings *settings = nullptr);

     core::IServer *CreateServer(
         const core::LoggerSettings &logSettings = DefaultLoggerSettings);

 private:
     std::string context_name_;
     bool initialised_;
     core::Logger *logger_;
     WebLoomSettings *settings_;
     core::FileServer *fileserver_;
};

#endif  // CONTEXT_H_

}   // namespace webloom
