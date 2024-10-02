/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <filesystem>

namespace AK {
    namespace fs = std::filesystem;
    enum FileType {
        Markdown,
        All,
        Undefined,
    };

    class File final {
    public:
        explicit File(const fs::path & path);
        [[nodiscard]] std::string get_filename() const;
        [[nodiscard]] FileType get_type() const;
        [[nodiscard]] std::string get_type_string() const;
        [[nodiscard]] std::string get_name() const;
    private:
        std::string _filename;
        FileType _type;
        std::string _name;
    };

    FileType get_file_type(const std::string& extension);
    std::shared_ptr<std::vector<File>> collect(const std::string & path, FileType file_type);
}