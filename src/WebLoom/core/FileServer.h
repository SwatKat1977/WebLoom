//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef CORE_FILESERVER_H_
#define CORE_FILESERVER_H_
#include <memory>
#include <string>
#include "WebLoomSettings.h"
#include "core/Logger.h"
#include "HttpContentType.h"

namespace webloom::core {

struct FileData {
    std::string contents;
    HttpContentType contentType;
};

class FileServer {
 public:
    explicit FileServer(core::Logger *logger,
                        const char *libmagicFile = nullptr);

    ~FileServer();

    std::unique_ptr<FileData> ServeFile(const std::string &filename);

    std::string DetermineContentType(const std::string& path);

 private:
    class Implementation;
    Implementation *implementation_;
    core::Logger *logger_;

    std::string GetFileExtension(const std::string& path);

    std::string ReadFile(const std::string& filePath, bool isText);
};

}   // namespace webloom::core

#endif  // CORE_FILESERVER_H_
