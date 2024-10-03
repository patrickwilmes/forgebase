/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once

#include <string>
#include <map>

namespace AK {
    class IniConfig final {
    public:
        IniConfig(const std::string& path);

        [[nodiscard]] std::string get_value(const std::string& key);
    private:
        std::map<std::string, std::string> _config{};
    };
}
