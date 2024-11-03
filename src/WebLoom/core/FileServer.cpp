//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include "magic.h"              // NOLINT(build/include_subdir)
#include "FileServer.h"
#include "HttpContentType.h"
#include "Platform.h"

namespace webloom::core {

static const std::unordered_map<std::string, HttpContentType> KnownMimeTypes = {
{"ico", HttpContentType::ImageXIcon},
{"png", HttpContentType::ImagePNG},
{"jpg", HttpContentType::ImageJPEG},
{"jpeg", HttpContentType::ImageJPEG},
{"gif", HttpContentType::ImageGIF},
{"webp", HttpContentType::ImageWebP},
{"txt", HttpContentType::TextPlain},
{"html", HttpContentType::TextHTML},
{"htm", HttpContentType::TextPlain}
};

constexpr char TEXTFORMAT_TEXT[] = "text";

class FileServer::Implementation {
 public:
     Implementation() : magic_handle_(nullptr), magic_initialised_(false) {
     }

    magic_t magic_handle_;
    bool magic_initialised_;
};

FileServer::FileServer(core::Logger* logger, const char *libmagicFile)
          : implementation_(new Implementation), logger_(logger) {
    // Open a magic cookie (handle) with the option to get MIME type
    implementation_->magic_handle_ = magic_open(MAGIC_MIME_TYPE);
    if (implementation_->magic_handle_ == nullptr) {
        throw std::runtime_error("Failed to initialize libmagic");
    }

    // Load the default magic database
    if (magic_load(implementation_->magic_handle_, libmagicFile) != 0) {
        magic_close(implementation_->magic_handle_);
        throw std::runtime_error("Failed to load magic database");
    }

    implementation_->magic_initialised_ = true;
}

FileServer::~FileServer() {
    if (implementation_->magic_initialised_) {
        implementation_->magic_initialised_ = false;
        magic_close(implementation_->magic_handle_);
    }
}

/**
 * @brief Serves a file by reading its contents and determining its MIME type.
 *
 * This function takes a filename, determines the MIME type of the file,
 * checks if it is a text format, and reads the file's contents accordingly.
 * It returns a `FileData` object containing the MIME type and file contents.
 *
 * @param filename A reference to the name of the file to be served.
 *                 The file should be accessible from the file system.
 *
 * @return FileData A `FileData` object that contains:
 *         - `mimeType`: The MIME type of the file, determined by
                         `GetMimeType`.
 *         - `contents`: The file contents as a string, read based on file
                         type.
 *
 * The function sets the `isTextFormat` flag to `true` if the file's MIME type
 * matches the `TEXTFORMAT_TEXT` prefix, indicating a text-based format. It
 * then reads the file's contents using `ReadFile`, passing the `isTextFormat`
 * flag to handle reading for either text or binary formats.
 */
std::unique_ptr<FileData> FileServer::ServeFile(const std::string &filename) {
    bool isTextFormat = false;

    if (!std::filesystem::exists(filename)) {
        logger_->LogWarn("Unable to server '%s' as file does not exist",
                         filename.c_str());
        return nullptr;
    }

    auto fileData = std::make_unique<FileData>();

    try {
        std::string contentTypeStr = DetermineContentType(filename);
        fileData->contentType = HttpContentTypeStringToEnum(contentTypeStr);

        if (contentTypeStr.size() >= strlen(TEXTFORMAT_TEXT) &&
            contentTypeStr.substr(
                0, strlen(TEXTFORMAT_TEXT)) == TEXTFORMAT_TEXT) {
            isTextFormat = true;
        }
    }
    catch (std::runtime_error& ex) {
        logger_->LogError(ex.what());
        return nullptr;
    }
    catch(std::invalid_argument &ex) {
        logger_->LogError(ex.what());
        return nullptr;
    }

    fileData->contents = ReadFile(filename, isTextFormat);
    return fileData;
}

std::string FileServer::DetermineContentType(const std::string& path) {
    auto extension = GetFileExtension(path);

    auto it = KnownMimeTypes.find(extension);

    if (it != KnownMimeTypes.end()) {
        return HttpContentTypeString(it->second);
    }

    // Use magic_file to get MIME type
    const char* mimeType = magic_file(implementation_->magic_handle_,
                                      path.c_str());

    if (mimeType == nullptr) {
        // Check if the error is due to an unsupported format
        const char* error = magic_error(implementation_->magic_handle_);

        if (error) {
            std::string errorMsg = error;

            // Handle specific cases: Unsupported format vs. internal error
            if (errorMsg.find("no magic") != std::string::npos ||
                errorMsg.find("unknown") != std::string::npos ||
                errorMsg.find("cannot") != std::string::npos) {
                // Unsupported mime type - revert back to plain text.
                return HttpContentTypeString(HttpContentType::TextPlain);
            } else {
                throw std::runtime_error("Internal libmagic error: " +
                                         errorMsg);
            }
        }

        // Fallback if error details are unclear
        return HttpContentTypeString (HttpContentType::TextPlain);
    }

    return std::string(mimeType);
}

std::string FileServer::GetFileExtension(const std::string& path) {
    size_t dotPos = path.find_last_of('.');
    if (dotPos == std::string::npos) {
        return "";
    }

    return path.substr(dotPos + 1);
}

std::string FileServer::ReadFile(const std::string& filePath, bool isText) {
    std::ios_base::openmode mode = isText ? std::ios::in : std::ios::binary;
    std::ifstream file(filePath, mode);

    std::string content;
    if (isText) {
        // Read text file
        std::ostringstream ss;
        ss << file.rdbuf();
        content = ss.str();
    } else {
        file.seekg(0, std::ios::end);
        size_t fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<char> buffer(fileSize);
        file.read(buffer.data(), fileSize);
        content.assign(buffer.begin(), buffer.end());
    }

    return content;
}

}   // namespace webloom::core
