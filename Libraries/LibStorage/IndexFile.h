/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once

#include <string>
#include <File.h>

namespace LibStorage {
    class IndexFile final {
    public:
        IndexFile(std::string  path, std::string  name, AK::FileType type);
        [[nodiscard]] std::string get_path() const;
        [[nodiscard]] std::string get_name() const;
        [[nodiscard]] AK::FileType get_type() const;
    private:
        std::string _path;
        std::string _name;
        AK::FileType _type;
    };
}