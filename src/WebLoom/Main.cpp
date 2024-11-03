//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#include <cstdlib>
#include <string>
#include "core/Platform.h"
#include "core/ThreadPool.h"
#include "core/LoggerSettings.h"
#include "core/Logger.h"
#include "Header.h"

int main(int argc, char** argv) {
    auto lc = webloom::core::LoggerSettings();

    lc.LogToConsole(true);

    auto logger = webloom::core::Logger(lc);
    logger.LogInfo("this is an info test");
    logger.LogCritical("this is a critical test");
    logger.LogError("this is an error test");
    logger.LogWarn("this is a warning  test");

    auto h = Header();
    h.Add("MyHeader1", "MyValue1");
    h.Add("MyHeader2", "MyValue2");

    printf("H1 %s\n", h.Get("MyHeader1")->c_str());
    printf("H2 %s\n", h.Get("MyHeader2")->c_str());

    auto inva = h.Get("Invalid");
    std::string v = (!inva) ? "<NONE>" : inva->c_str();
    printf("Invalid %s\n", v.c_str());

    try {
        h.Add("MyHeader2", "MyValue2");
    }
    catch (std::runtime_error ex) {
        printf("As expected, error returned : %s\n", ex.what());
    }

    return EXIT_SUCCESS;
}
