// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <stdlib.h>
#include <string.h>
#include "headers/inih_parser.h"
#include "headers/string_helper.h"
#include "../submodule/log.c-patched/src/log.h"

int parse_config_cb(void* user, const char* section, const char* name,
                                const char* value)
{
        struct ini_config* config = (struct ini_config*)user;

        #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
        if (MATCH("TELEGRAM", "bot_token")) {
                config->bot_token = strdup(value);
        } else if (MATCH("TELEGRAM", "command_prefix")) {
                char* tmpptr = strdup(value);
                config->command_prefix = *tmpptr;
                free(tmpptr);
        }  else if (MATCH("TELEGRAM", "bot_username")) {
                config->bot_username = strdup(value);
        } else if (MATCH("DEBUG", "enable_all_log")) {
                char* tmpptr = strdup(value);
                config->enable_all_log = FadhilRiyanto::string_utils::string_helper::str2bool(tmpptr);
                free(tmpptr);
        } else if (MATCH("DEBUG", "enable_command_debug_log")) {
                char* tmpptr = strdup(value);
                config->enable_command_debug_log = FadhilRiyanto::string_utils::string_helper::str2bool(tmpptr);
                free(tmpptr);
        } else if (MATCH("DEBUG", "enable_pool_start_log")) {
                char* tmpptr = strdup(value);
                config->enable_pool_start_log = FadhilRiyanto::string_utils::string_helper::str2bool(tmpptr);
                free(tmpptr);
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

void ini_show_config(struct ini_config *config)
{
        log_info("config loaded \"bot_token\" = \"%s\"", config->bot_token);
        log_info("config loaded \"enable_all_log\" = \"%s\"", config->enable_all_log == 1 ? "true" : "false");
        log_info("config loaded \"command_prefix\" = \"%c\"", config->command_prefix);
        log_info("config loaded \"bot_username\" = \"%s\"", config->bot_username);
        
        
}