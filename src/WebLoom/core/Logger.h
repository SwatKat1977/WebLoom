//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef CORE_LOGGER_H_
#define CORE_LOGGER_H_
#include "LoggerSettings.h"

namespace webloom::core {

class Logger {
 public:
    explicit Logger(const LoggerSettings& settings);

    void LogDebug(const char* format, ...);

    void LogError(const char* format, ...);

    void LogInfo(const char* format, ...);

    void LogCritical(const char* format, ...);

    void LogWarn(const char* format, ...);

 private:
    LoggerSettings settings_;
};

}   // namespace webloom::core

#endif  // CORE_LOGGER_H_
