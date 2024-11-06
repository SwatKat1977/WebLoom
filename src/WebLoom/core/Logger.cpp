//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <cstdarg>
#include <memory>
#include <string>
#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Logger.h"

namespace webloom::core {

static constexpr const char* LOGGER_NAME = "WebLoom";

Logger::Logger(const LoggerSettings& settings) : settings_(settings) {
    spdlog::init_thread_pool(settings_.ThreadSize(),
                             settings_.ThreadCount());

    std::vector<spdlog::sink_ptr> sinks;

    if (settings_.LogToConsole()) {
        auto stdout_sink = \
            std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
        sinks.push_back(stdout_sink);
    }

    if (!settings_.LogFilename().empty()) {
        if (settings_.MaxFileSize()) {
            try {
                auto sink = std::make_shared<
                    spdlog::sinks::rotating_file_sink_mt> (
                        settings_.LogFilename(),
                        settings_.MaxFileSize(),
                        settings_.MaxFileCount());
                sink->set_level(spdlog::level::debug);
                sinks.push_back(sink);
            }
            catch (const spdlog::spdlog_ex& ex) {
                std::string errStr =
                    std::string("Unable to initialise rotating file log "
                                "sink, reason: ") +
                    std::string(ex.what());
                throw std::runtime_error(errStr);
            }
        } else {
            try {
                const bool truncate = true;
                auto sink = std::make_shared<
                    spdlog::sinks::basic_file_sink_mt> (
                        settings_.LogFilename().c_str(),
                        truncate);
                sink->set_level(spdlog::level::debug);
                sinks.push_back(sink);
            }
            catch (const spdlog::spdlog_ex& ex) {
                std::string errStr =
                    std::string("Unable to initialise file log sink, "
                                "reason: ") +
                    std::string(ex.what());
                throw std::runtime_error(errStr);
            }
        }
    }

    auto logger = std::make_shared<spdlog::async_logger> (
        LOGGER_NAME,
        sinks.begin(),
        sinks.end(),
        spdlog::thread_pool(),
        spdlog::async_overflow_policy::block);

    logger->set_level(spdlog::level::debug);

    spdlog::register_logger(logger);

    // Set the log format, based on the formatting pattern flags:
    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
    spdlog::set_pattern(settings_.LogFormat());
}

void Logger::LogDebug(const char* format, ...) {
    va_list args;
    va_start(args, format);

    // Allocate a sufficiently large buffer
    char buffer[1024];
    vsnprintf(buffer, sizeof (buffer), format, args);

    va_end(args);

    spdlog::get(LOGGER_NAME)->debug(buffer);
}

void Logger::LogInfo(const char* format, ...) {
    va_list args;
    va_start(args, format);

    // Allocate a sufficiently large buffer
    char buffer[1024];
    vsnprintf(buffer, sizeof (buffer), format, args);

    va_end(args);

    spdlog::get(LOGGER_NAME)->info(buffer);
}

void Logger::LogCritical(const char* format, ...) {
    va_list args;
    va_start(args, format);

    // Allocate a sufficiently large buffer
    char buffer[1024];
    vsnprintf(buffer, sizeof (buffer), format, args);

    va_end(args);

    spdlog::get(LOGGER_NAME)->critical(buffer);
}

void Logger::LogError(const char* format, ...) {
    va_list args;
    va_start(args, format);

    // Allocate a sufficiently large buffer
    char buffer[1024];
    vsnprintf(buffer, sizeof (buffer), format, args);

    va_end(args);

    spdlog::get(LOGGER_NAME)->error(buffer);
}

void Logger::LogWarn(const char* format, ...) {
    va_list args;
    va_start(args, format);

    // Allocate a sufficiently large buffer
    char buffer[1024];
    vsnprintf(buffer, sizeof (buffer), format, args);

    va_end(args);

    spdlog::get(LOGGER_NAME)->warn(buffer);
}

}   // namespace webloom::core
