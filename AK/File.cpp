/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "File.h"

#include <utility>
#include <filesystem>
#include <iostream>


AK::File::File(const fs::path &path): _filename(std::move(path.string())),
                                      _type(get_file_type(path.extension())),
                                      _name(path.filename().string()) {
}

std::string AK::File::get_filename() const {
    return _filename;
}

AK::FileType AK::File::get_type() const {
    return _type;
}

std::string AK::File::get_type_string() const {
    switch (_type) {
        case Markdown:
            return "Markdown";
        default: return "Undefined";
    }
}

std::string AK::File::get_name() const {
    return _name;
}

AK::FileType AK::get_file_type(const std::string &extension) {
    if (extension == ".md") {
        return Markdown;
    }
    return Undefined;
}

std::shared_ptr<std::vector<AK::File> > AK::collect(const std::string &path, FileType type) {
    auto files = std::make_shared<std::vector<AK::File> >();
    if (fs::exists(path) && fs::is_directory(path)) {
        for (const auto &entry: fs::recursive_directory_iterator(path)) {
            if (entry.is_regular_file()) {
                if (const auto &entry_path = entry.path();
                    get_file_type(entry_path.extension()) == type || type == All) {
                    auto absolute_path = absolute(entry_path);
                    files->emplace_back(absolute_path);
                }
            }
        }
    } else {
        std::cerr << "Vault location doesn't exist, or is not a valid directory!" << std::endl;
    }
    return files;
}
