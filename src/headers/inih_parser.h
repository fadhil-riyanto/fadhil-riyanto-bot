// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef INIH_PARSER_H
#define INIH_PARSER_H

struct ini_config {
        char*           bot_token;
};

int parse_config_cb(void* user, const char* section, const char* name,
                                const char* value);

#endif