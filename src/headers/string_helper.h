// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <algorithm>
#include <cctype>
#include <string>

namespace FadhilRiyanto::string_utils {

class string_helper {
public:
        static std::string string_lowercase(std::string inp) ;
        static bool str2bool(std::string inp);
        static std::string bool2str(bool inp);
        static constexpr unsigned int str2int(const char* str, int h = 0);
};

}

#endif