/*
 * Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "UserSpace.h"
#include <memory>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <string>
#include <filesystem>
#include <assert.h>
#include "Logging.h"

namespace fs = std::filesystem;

const std::string config_dir = ".config/forgebase/";
const std::string config_file = "forge.ini";

std::string compute_configuration_path() {
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    std::string home = homedir;

    std::string config_folder = home + "/" + config_dir;
    /*
     * TODO - introduce proper error handling here in
     * addition to assert by also having a logger.
     * The error should be propaged to another level
     * or even terminate the appliation, as it doesn't
     * make any sense to continue if user settings cannot
     * be located / created.
     */
    if (!fs::exists(config_folder)) {
        AK::debug("Configuration folder doesn't exist! Creating...");
        assert(mkdir(config_folder.c_str(), 0755)==0);
    }
    return config_folder;
}

std::string compute_full_configuration_path() {
    std::string config_folder = compute_configuration_path();
    std::string full_config_path = config_folder + config_file;
    return full_config_path;
}

AK::UserSpace::UserSpace(): _config_home(compute_configuration_path()) {
    auto config_location = compute_full_configuration_path();
    debug("Initializing ini configuration at config location " + config_location + " ...");
    _ini_config = std::make_unique<IniConfig>(config_location);
    debug("Initialization of ini file successful!");
}

std::string AK::UserSpace::get_property(const std::string& key) {
    auto value = _ini_config->get_value(key);
    debug("Getting Property for key " + key + " with value " + value);
    return value;
}

std::string AK::UserSpace::get_config_home() {
    return _config_home;
}
