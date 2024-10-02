/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "CodeRepository.h"

LibRepository::CodeRepository::CodeRepository(const std::string &location): FileIndexer(location) {
}

std::shared_ptr<std::vector<AK::File>> LibRepository::CodeRepository::get_files_to_index() const {
    return collect(_location, AK::All);
}
