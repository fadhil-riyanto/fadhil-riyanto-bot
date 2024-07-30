// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <stdlib.h>
#include <string.h>
#include "headers/inih_parser.h"

int parse_config_cb(void* user, const char* section, const char* name,
                                const char* value)
{
        struct ini_config* config = (struct ini_config*)user;

        #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
        if (MATCH("TELEGRAM", "bot_token")) {
                config->bot_token = strdup(value);
        } else if (MATCH("RUNTIME", "quiet_logger")) {
                char* tmpptr = strdup(value);
                config->logger = (strcmp(tmpptr, "true") == 0) ? true : false;
                free(tmpptr);
        } else if (MATCH("TELEGRAM", "command_prefix")) {
                char* tmpptr = strdup(value);
                config->command_prefix = tmpptr[0];
                free(tmpptr);
        } else if (MATCH("TELEGRAM", "bot_username")) {
                config->bot_username = strdup(value);
        } else {
                return 0;
        }
        return 1;
}


void ini_free_mem(struct ini_config *config)
{
        free(config->bot_token);
        free(config->bot_username);
}