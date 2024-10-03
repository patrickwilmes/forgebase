/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once

#include <string>

namespace AK {
    enum LogLevel {
        DEBUG,
        INFO,
        WARN,
        ERROR,
    };

    void error(const std::string & message);
    void info(const std::string & message);
    void warn(const std::string & message);
    void debug(const std::string & message);
}

