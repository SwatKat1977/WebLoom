//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef CORE_LOGGERSETTINGS_H_
#define CORE_LOGGERSETTINGS_H_
#include <string>

namespace webloom::core {

class LoggerSettings {
 public:
    /**
    * @brief Constructs a LoggerSettings object with default values.
    *
    * Initializes the logger settings with default values for the log filename,
    * console logging, file logging, maximum file count, maximum file size,
    * thread count, and thread size.
    */
    LoggerSettings() : log_filename_(DEFAULT_LOG_FILENAME),
                       log_to_console_(true),
                       log_to_file_(false),
                       max_file_count_(MAX_FILE_COUNT),
                       max_file_size_(MAX_FILE_SIZE),
                       thread_count_(DEFAULT_LOGGER_THREAD_COUNT),
                       thread_size_(DEFAULT_LOGGER_THREAD_SIZE),
                       log_format_(DEFAULT_LOG_FORMAT) {
    }

    /**
     * @brief Retrieves the log filename.
     *
     * @return const std::string& The current log filename.
     */
    const std::string &LogFilename() const {
        return log_filename_;
    }

    /**
     * @brief Sets the log filename.
     *
     * @param log_filename The new log filename to be set.
     */
    void LogFilename(const std::string& log_filename) {
        log_filename_ = log_filename;
    }

    /**
     * @brief Checks if logging to the console is enabled.
     *
     * @return bool True if logging to console is enabled, false otherwise.
     */
    bool LogToConsole() const {
        return log_to_console_;
    }

    /**
     * @brief Enables or disables logging to the console.
     *
     * @param log_to_console Set to true to enable console logging,
     *                       false to disable it.
     */
    void LogToConsole(bool log_to_console) {
        log_to_console_ = log_to_console;
    }

    /**
     * @brief Checks if logging to a file is enabled.
     *
     * @return bool True if logging to file is enabled, false otherwise.
     */
    bool LogToFile() const {
        return log_to_file_;
    }

    /**
     * @brief Enables or disables logging to a file.
     *
     * @param log_to_file Set to true to enable file logging,
     *                    false to disable it.
     */
    void LogToFile(bool log_to_file) {
        log_to_file_ = log_to_file;
    }

    /**
     * @brief Retrieves the maximum file count for log rotation.
     *
     * @return unsigned int The maximum number of log files to retain.
     */
    unsigned int MaxFileCount() const {
        return max_file_count_;
    }

    /**
     * @brief Sets the maximum file count for log rotation.
     *
     * @param max_file_count The maximum number of log files to retain.
     */
    void MaxFileCount(unsigned int max_file_count) {
        max_file_count_ = max_file_count;
    }

    /**
     * @brief Retrieves the maximum size of the log file.
     *
     * @return unsigned int The maximum size (in bytes) of a log file
     *         before it is rotated.
     */
    unsigned int MaxFileSize() const {
        return max_file_size_;
    }

    /**
     * @brief Sets the maximum size of the log file.
     *
     * @param max_file_size The maximum size (in bytes) of a log file
     *                      before it is rotated.
     */
    void MaxFileSize(unsigned int max_file_size) {
        max_file_size_ = max_file_size;
    }

    /**
     * @brief Retrieves the number of threads used for logging.
     *
     * @return unsigned int The number of threads used for asynchronous logging.
     */
    unsigned int ThreadCount() const {
        return thread_count_;
    }

    /**
     * @brief Sets the number of threads used for logging.
     *
     * @param thread_count The number of threads to be used for logging.
     */
    void ThreadCount(unsigned int thread_count) {
        thread_count_ = thread_count;
    }

    /**
     * @brief Retrieves the size of the thread queue for logging.
     *
     * @return unsigned int The size of the log message queue for
     *         asynchronous logging.
     */
    unsigned int ThreadSize() const {
        return thread_size_;
    }

    /**
     * @brief Sets the size of the thread queue for logging.
     *
     * @param thread_size The maximum size of the log message queue for
     *                    asynchronous logging.
     */
    void ThreadSize(unsigned int thread_size) {
        thread_size_ = thread_size;
    }

    std::string LogFormat() const {
        return log_format_;
    }

    void LogFormat(std::string format) {
        log_format_ = format;
    }

 private:
    std::string log_filename_;
    bool log_to_console_;
    bool log_to_file_;
    unsigned int max_file_count_;
    unsigned int max_file_size_;
    unsigned int thread_count_;
    unsigned int thread_size_;
    std::string log_format_;

    static constexpr unsigned int DEFAULT_LOGGER_THREAD_SIZE = 8192;
    static constexpr unsigned int DEFAULT_LOGGER_THREAD_COUNT = 1;
    static constexpr const char *DEFAULT_LOG_FILENAME = "main.log";
    static constexpr unsigned int MAX_FILE_COUNT = 1;
    static constexpr unsigned int MAX_FILE_SIZE = 1;

    static constexpr const char* DEFAULT_LOG_FORMAT =
        "%Y-%m-%d %H:%M:%S %^%l%$ %v";
};

}   // namespace webloom::core

#endif  // CORE_LOGGERSETTINGS_H_
