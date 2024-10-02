/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "IndexFile.h"

#include <utility>

LibStorage::IndexFile::IndexFile(std::string path, std::string name,
    AK::FileType type): _path(std::move(path)), _name(std::move(name)), _type(type){
}

std::string LibStorage::IndexFile::get_path() const {
    return _path;
}

std::string LibStorage::IndexFile::get_name() const {
    return _name;
}

AK::FileType LibStorage::IndexFile::get_type() const {
    return _type;
}
