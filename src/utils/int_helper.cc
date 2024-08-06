// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "../headers/int_helper.h"
#include <string>

bool FadhilRiyanto::int_utils::int_helper::int2bool(int src)
{
        return (src == 1) ? true : false;
}

std::string FadhilRiyanto::int_utils::int_helper::int2bool2str(int src)
{
        return (src == 1) ? "true" : "false";
}