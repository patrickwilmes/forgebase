/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "Forgebase.h"
#include <Obsidian.h>
#include <CodeRepository.h>
#include <IndexFile.h>
#include <FileIndexStore.h>
#include <vector>
#include <memory>
#include <algorithm>

void Forgebase::index() {
    const auto obsidian_result = LibObsidian::Obsidian("/home/patrick/second-brain/").get_files_to_index();
    const auto code_result = LibRepository::CodeRepository("/home/patrick/projects/").get_files_to_index();

    const auto merged_results = std::make_shared<std::vector<AK::File>>();
    merged_results->reserve(obsidian_result->size() + code_result->size());
    merged_results->insert(merged_results->end(), obsidian_result->begin(), obsidian_result->end());
    merged_results->insert(merged_results->end(), code_result->begin(), code_result->end());

    const auto index_files = std::make_shared<std::vector<LibStorage::IndexFile>>();
    index_files->reserve(merged_results->size());
    std::transform(merged_results->begin(), merged_results->end(), std::back_inserter(*index_files), [](const AK::File &file) {
        return LibStorage::IndexFile(file.get_filename(), file.get_name(), file.get_type());
    });

    auto storage = LibStorage::default_file_index_store();
    storage->write_to_index(index_files);
}

void Forgebase::search(const std::string &search) {
}
