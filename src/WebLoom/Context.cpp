//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <stdexcept>
#include "core/Platform.h"
#include "core/HttpServer.h"
#include "Context.h"

namespace webloom {

Context::Context(std::string contextName, WebLoomSettings *settings)
       : context_name_(contextName), initialised_(false), logger_(nullptr) {
    auto staticDir = settings->StaticWebsiteDir();
    if (staticDir.empty() || staticDir.back() != '/') {
        // Append '/' at the end of the path as one doesn't exist.
        staticDir += '/';
        settings->StaticWebsiteDir(staticDir);
    }

    auto templatesDir = settings->TemplatesDir();
    if (templatesDir.empty() || templatesDir.back() != '/') {
        // Append '/' at the end of the path as one doesn't exist.
        templatesDir += '/';
        settings->TemplatesDir(templatesDir);
    }

    settings_ = !settings ? new WebLoomSettings() : settings;
}

core::IServer *Context::CreateServer(const core::LoggerSettings& logSettings) {
    logger_ = new core::Logger(logSettings);

    std::string libmagicDB = settings_->LibmagicDB();
    const char* dbPath = (libmagicDB.empty()) ? nullptr : libmagicDB.c_str();
    fileserver_ = new core::FileServer(logger_, dbPath);

    return new core::HttpServer(logger_, settings_, fileserver_);
}

}   // namespace webloom
