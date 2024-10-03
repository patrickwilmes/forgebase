/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "Obsidian.h"
#include <Logging.h>

LibObsidian::Obsidian::Obsidian(const std::string & vault_location): FileIndexer(vault_location) {
    AK::debug("Obsidian Vault at " + vault_location);
}

std::shared_ptr<std::vector<AK::File> > LibObsidian::Obsidian::get_files_to_index() const {
    return collect(_location, AK::Markdown);
}
