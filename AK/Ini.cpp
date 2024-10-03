/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "Ini.h"
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include "Logging.h"

namespace fs = std::filesystem;

AK::IniConfig::IniConfig(const std::string& path) {
    AK::info("Loading ini configuration ...");
    if (!fs::exists(path)) {
        AK::error("Ini configuration path " + path + " doesn't exist");
        throw std::runtime_error("Given path to configuration file (ini) " + path + " doesn't exist!");
    }
    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line)) {
        AK::debug("Reading config line " + line);
        //line.erase(0, line.find_last_not_of(" \t"));
        //line.erase(line.find_last_not_of(" \t") + 1);
        //AK::debug("clean config line line " + line);

        if (line.empty() || line[0] == '#' || line[0] == ';') {
            AK::debug("Figured that line " + line + " is empty");
            continue;
        }

        std::size_t delimeter_pos = line.find('=');
        AK::debug("Delimeter position is " + std::to_string(delimeter_pos));
        if (delimeter_pos != std::string::npos) {
            std::string key = line.substr(0, delimeter_pos);
            std::string value = line.substr(delimeter_pos + 1);

            //key.erase(0, line.find_last_not_of(" \t"));
            //key.erase(line.find_last_not_of(" \t") + 1);
            //value.erase(0, line.find_last_not_of(" \t"));
            //value.erase(line.find_last_not_of(" \t") + 1);
            AK::debug("Loading key " + key + " with value " + value);
            _config[key] = value;
        }
    }
    file.close();
    AK::info("Ini configuration successfully initialized!");
}

std::string AK::IniConfig::get_value(const std::string& key) {
    return _config[key];
}
