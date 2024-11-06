//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef WEBLOOMSETTINGS_H_
#define WEBLOOMSETTINGS_H_
#include <string>

namespace webloom {

using NetworkPort = unsigned int;

const char DEFAULT_STATIC_WEBSITE_DIR[] = "./static_websites";
const char DEFAULT_TEMPLATE_DIR[] = "./templates";
const NetworkPort DEFAULT_NETWORK_PORT = 8080;
const char DEFAULT_LIBMAGIC_DB[] = "";

class WebLoomSettings {
 public:
    WebLoomSettings() : static_website_dir_(DEFAULT_STATIC_WEBSITE_DIR),
                        templates_dir_(DEFAULT_TEMPLATE_DIR),
                        network_port_(DEFAULT_NETWORK_PORT),
                        libmagic_db_(DEFAULT_LIBMAGIC_DB) {
    }

    std::string StaticWebsiteDir() { return static_website_dir_; }
    void StaticWebsiteDir(const std::string &dir) { static_website_dir_ = dir ;}

    std::string TemplatesDir() { return templates_dir_;}
    void TemplatesDir(const std::string &dir) { templates_dir_ = dir; }

    NetworkPort ServerNetworkPort() { return network_port_;}
    void ServerNetworkPort(NetworkPort port) { network_port_ = port;}

    std::string LibmagicDB () { return libmagic_db_; }
    void LibmagicDB(const std::string &db) { libmagic_db_ = db; }

 private:
    std::string static_website_dir_;
    std::string templates_dir_;
    NetworkPort network_port_;
    std::string libmagic_db_;
};

}   // namespace webloom

#endif  // WEBLOOMSETTINGS_H_
