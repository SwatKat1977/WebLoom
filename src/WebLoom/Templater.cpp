//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#pragma warning(push)
#pragma warning(disable : 4244)
#include <inja/inja.hpp>
#pragma warning(pop)
#include <nlohmann/json.hpp>
#include "Templater.h"
#include "HttpContentType.h"
#include "WebLoomExceptions.h"
#include "core/HttpStatus.h"

namespace webloom {

class Templater::Implementation {
public:
    inja::Environment inja_environment;
};

/**
    * @brief Renders a template file and returns an HTTP response with its
    * contents.
    *
    * This function locates the specified template file within the configured
    * template directory, reads its contents, and prepares an HTTP response
    * with a successful status. If the file is not found, an exception is
    * thrown.
    *
    * @param filename The name of the template file to render, relative to the
    *                 templates directory.
    * @param args Optional key-value arguments for template variables, passed
    *             as a map of strings.
    *
    * @return A dynamically allocated Response object containing:
    *         - HTTP status `OK` (200),
    *         - File contents as the body,
    *         - File content type as the response content type.
    *
    * @throws TemplateNotFound If the specified file cannot be located.
    */
Response *Templater::RenderTemplate(std::string filename,
                                    TemplateArguments args) {
    std::string templateFile = settings_->TemplatesDir() + filename;
    nlohmann::json data;

    auto fileData = fileserver_->ServeFile(templateFile);
    if (!fileData) {
        throw TemplateNotFound("Unable to find file '" + templateFile + "'");
    }

    for (const auto& pair : args) {
        data[pair.first] = pair.second;
    }

    try {
        std::string rendered = impl_->inja_environment.render(
            fileData->contents, data);
        return new Response(core::HttpStatus::OK,
                            rendered,
                            fileData->contentType);
    }
    catch (const inja::RenderError& ex) {
        std::string exception = "Render error: " + std::string(ex.what());
        throw TemplateRenderFailed(exception);
    }

    return nullptr;
}

/**
 * @brief Initializes the Templater singleton with required dependencies.
 *
 * This function sets up the Templater with a logger, configuration settings,
 * and a file server, allowing it to render templates with these dependencies.
 * It should be called once before using the Templater instance.
 *
 * @param logger Pointer to the Logger instance used for logging operations.
 * @param settings Pointer to WebLoomSettings for accessing configuration, such
 *                 as template directories.
 * @param fileserver Pointer to the FileServer instance for serving template
 *                   files.
 */
void Templater::Initialise(core::Logger* logger,
                           WebLoomSettings* settings,
                           core::FileServer* fileserver) {
    impl_ = new Implementation ();
    logger_ = logger;
    settings_ = settings;
    fileserver_ = fileserver;
}

}   // namespace webloom
