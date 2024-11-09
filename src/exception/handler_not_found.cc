// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "../headers/error.h"

char const* FadhilRiyanto::error::handler_not_found::what() {
        return "command handler is not found, maybe you type a wrong command";
}