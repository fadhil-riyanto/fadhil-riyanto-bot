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
        bool            logger;
        char            command_prefix;
        char*           bot_username;
};

int parse_config_cb(void* user, const char* section, const char* name,
                                const char* value);

void ini_free_mem(struct ini_config *config);

#endif