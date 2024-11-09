// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "../headers/string_helper.h"
#include <algorithm>
#include <string>
#include <sstream>

namespace FadhilRiyanto::string_utils {


std::string string_helper::string_lowercase(std::string inp) 
{
        std::transform(inp.begin(), inp.end(), inp.begin(), [](unsigned char c) {
                return std::tolower(c);
        });
        return inp;
}

bool string_helper::str2bool(std::string inp) 
{
        std::string sanitized_inp = FadhilRiyanto::string_utils::string_helper::string_lowercase(inp);
        // printf("%s\n", sanitized_inp.c_str());

        if (sanitized_inp.compare("true") == 0) {
                return true;
        }  else {
                return false;
        }
}

std::string string_helper::bool2str(bool inp)
{
        return (inp == true) ? "true" : "false";
}

std::string string_helper::split_n_index(std::string src, int index)
{
        std::istringstream iss(src);
        std::string s;

        int initial = 0;

        while(getline(iss, s, ' ' )) {
                
                if (initial == index) {
                        return s;
                }

                initial++;
        }

        return 0;

}

}