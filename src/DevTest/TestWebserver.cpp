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
#include "Request.h"
#include "RequestMethod.h"
#include "Response.h"
#include "RouteHandler.h"

class AdminWebsite {
public:
    AdminWebsite() {
        auto methods = { webloom::RequestMethod::Get, webloom::RequestMethod::Put };
        WEBLOOM_ROUTE("/myroute", methods, HandleLogin);
    }

    webloom::Response* HandleLogin (webloom::Request *request) {
        std::string body = "<html><head><title>I am a teapot</title></head><body>Test</body></html>";
        return new webloom::Response(
            webloom::core::HttpStatus::OK,
            body, webloom::core::HttpContentType::TextHTML);
    }
};

#include "RouteHandler.h"
int main() {
    AdminWebsite test;

#ifdef _TEST_CODE_
    webloom::Request* re = new webloom::Request(webloom::RequestMethod::Get, webloom::HttpVersion::HTTP_1_0, "/bob");

    auto a = webloom::RouteHandler::Instance().HandleRequest ("invalid", webloom::RequestMethod::Delete, re);
    if (!a) { printf ("Invalid correct\n"); }
    printf("[DEBUG] Should return 0 to invalid route : %d\n",
           webloom::RouteHandler::Instance().IsValidRoute("invalid", webloom::RequestMethod::Head));

    auto b = webloom::RouteHandler::Instance().HandleRequest ("/myroute", webloom::RequestMethod::Get, re);
    if (b) { printf ("Valid correct\n"); }
    printf ("[DEBUG] Should return 0 to invalid route : %d\n",
            webloom::RouteHandler::Instance ().IsValidRoute ("/myroute", webloom::RequestMethod::Head));
    printf ("[DEBUG] Should return 1 to invalid route : %d\n",
        webloom::RouteHandler::Instance ().IsValidRoute ("/myroute", webloom::RequestMethod::Put));
#endif

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
