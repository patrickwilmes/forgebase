/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once

#include "Ini.h"
#include <string>
#include <memory>

namespace AK {
    class UserSpace final {
    public:
        UserSpace();

        [[nodiscard]] std::string get_property(const std::string& key);

        [[nodiscard]] std::string get_config_home();

    private:
        std::unique_ptr<IniConfig> _ini_config{};
        std::string _config_home;
    };
}
