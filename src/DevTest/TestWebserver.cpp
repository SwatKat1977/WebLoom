//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <iostream>
#include <memory>
#include <string>
#include "Context.h"
#include "core/LoggerSettings.h"
#include "WebLoomSettings.h"
#include "HttpContentType.h"
#include "core/HttpStatus.h"
#include "core/Platform.h"
#include "Request.h"
#include "RequestMethod.h"
#include "Response.h"
#include "RouteHandler.h"
#include "Templater.h"
#include "WebLoomExceptions.h"

const std::string PAGE_NOT_FOUND = "<html>"
                                   "<head><title>Page Not Found</title></head>"
                                   "<body>Page is not found (404)</body>"
                                   "</html>";

class AdminWebsite {
public:
    AdminWebsite() {
        auto methods = { webloom::RequestMethod::Get, webloom::RequestMethod::Put };
        WEBLOOM_ROUTE("/myroute", methods, HandleLogin);
    }

    webloom::Response* HandleLogin (webloom::Request *request) {
        webloom::TemplateArguments testArgs = {
            {"website_name", "Multi-Type Webpage | Index"},
            {"who", "A.N.Other"} };

        try {
            return webloom::Templater::Instance().RenderTemplate("test.html",
                                                                 testArgs);
        }
        catch (webloom::TemplateNotFound& ex) {
            std::cout << "[EXCEPTION] " << ex.what () << "\n";
            return new webloom::Response(
                webloom::core::HttpStatus::NotFound,
                PAGE_NOT_FOUND, webloom::HttpContentType::TextHTML);
        }
        catch (webloom::TemplateRenderFailed& ex) {
            std::cout << "[EXCEPTION] " << ex.what () << "\n";
            return new webloom::Response (
                webloom::core::HttpStatus::NotFound,
                PAGE_NOT_FOUND, webloom::HttpContentType::TextHTML);
        }

        return new webloom::Response(
            webloom::core::HttpStatus::OK,
            "OK", webloom::HttpContentType::TextHTML);
    }
};

int main() {
    AdminWebsite test;

    webloom::WebLoomSettings webloomSettings;
    webloom::Context *context = nullptr;

    try {
        //context = new webloom::Context("Dev Test");
        context = new webloom::Context("Dev Test", &webloomSettings);
    }
    catch (std::runtime_error& ex) {
        std::cout << "Excepion : " << ex.what();
        return EXIT_FAILURE;
    }

    webloom::core::LoggerSettings loggerSettings;
    loggerSettings.LogToFile(true);
    loggerSettings.MaxFileSize(40960);

    auto *server = context->CreateServer(loggerSettings);

    server->Run();

    return EXIT_SUCCESS;
}
