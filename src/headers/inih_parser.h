// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef INIH_PARSER_H
#define INIH_PARSER_H

#include "../internal_config.h"

struct ini_config {
        char*           bot_token;
        bool            enable_all_log;
        bool            show_startup_ini_config;
        bool            enable_command_debug_log;
        bool            enable_pool_start_log;
        bool            enable_thread_queue_debug;
        bool            enable_on_create_thread_event;
        bool            enable_on_joined_thread_event;
        bool            enable_thread_bug_log;
        
        char            command_prefix;
        char*           bot_username;
        int             queue_depth;
        int             queue_eventloop_sleep_ms;

        char*           module[bot_module_N];
};

int parse_config_cb(void* user, const char* section, const char* name,
                                const char* value);

void ini_free_mem(struct ini_config *config);
void ini_show_config(struct ini_config *config);

int ini_load_config(const char *filename, struct ini_config* config);

#endif