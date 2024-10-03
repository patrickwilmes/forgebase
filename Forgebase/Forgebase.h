/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#pragma once

#include <string>
#include <UserSpace.h>

namespace Core {
    class Forgebase final {
    public:
        Forgebase();

        void index();

        void search(const std::string& search);
    private:
        AK::UserSpace _user_space;
    };
}
