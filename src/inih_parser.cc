// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include "headers/inih_parser.h"
#include "headers/string_helper.h"
#include "../submodule/log.c-patched/src/log.h"
#include "../submodule/inih/ini.h"
#include "internal_config.h"

// int counter = 0;

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
        } else if (MATCH("DEBUG", "show_startup_ini_config")) {
                char* tmpptr = strdup(value);
                config->show_startup_ini_config = FadhilRiyanto::string_utils::string_helper::str2bool(tmpptr);
                free(tmpptr);
        } else if (MATCH("DEBUG", "enable_command_debug_log")) {
                char* tmpptr = strdup(value);
                config->enable_command_debug_log = FadhilRiyanto::string_utils::string_helper::str2bool(tmpptr);
                free(tmpptr);
        } else if (MATCH("DEBUG", "enable_pool_start_log")) {
                char* tmpptr = strdup(value);
                config->enable_pool_start_log = FadhilRiyanto::string_utils::string_helper::str2bool(tmpptr);
                free(tmpptr);
        } else if (MATCH("DEBUG", "enable_thread_queue_debug")) {
                char* tmpptr = strdup(value);
                config->enable_thread_queue_debug = FadhilRiyanto::string_utils::string_helper::str2bool(tmpptr);
                free(tmpptr);
        } else if (MATCH("DEBUG", "enable_on_create_thread_event")) {
                char* tmpptr = strdup(value);
                config->enable_on_create_thread_event = FadhilRiyanto::string_utils::string_helper::str2bool(tmpptr);
                free(tmpptr);
        } else if (MATCH("DEBUG", "enable_on_joined_thread_event")) {
                char* tmpptr = strdup(value);
                config->enable_on_joined_thread_event = FadhilRiyanto::string_utils::string_helper::str2bool(tmpptr);
                free(tmpptr);
        } else if (MATCH("DEBUG", "enable_thread_bug_log")) {
                char* tmpptr = strdup(value);
                config->enable_thread_bug_log = FadhilRiyanto::string_utils::string_helper::str2bool(tmpptr);
                free(tmpptr);
        } else if (MATCH("RUNTIME", "queue_depth")) {
                config->queue_depth = atoi(value);
        }  else if (MATCH("RUNTIME", "queue_eventloop_sleep_ms")) {
                config->queue_eventloop_sleep_ms = atoi(value);
        }  else {
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
        if (config->show_startup_ini_config == true) {
                log_info("config loaded \"[TELEGRAM] bot_token\" = \"%s\"", config->bot_token);
                log_info("config loaded \"[TELEGRAM] command_prefix\" = \"%c\"", config->command_prefix);
                log_info("config loaded \"[TELEGRAM] bot_username\" = \"%s\"", config->bot_username);

                log_info("config loaded \"[DEBUG] enable_all_log\" = \"%s\"", 
                        FadhilRiyanto::string_utils::string_helper::bool2str(config->enable_all_log).c_str());
                log_info("config loaded \"[DEBUG] enable_command_debug_log\" = \"%s\"", 
                        FadhilRiyanto::string_utils::string_helper::bool2str(config->enable_command_debug_log).c_str());
                log_info("config loaded \"[DEBUG] enable_pool_start_log\" = \"%s\"", 
                        FadhilRiyanto::string_utils::string_helper::bool2str(config->enable_pool_start_log).c_str());
                log_info("config loaded \"[DEBUG] enable_thread_queue_debug\" = \"%s\"", 
                        FadhilRiyanto::string_utils::string_helper::bool2str(config->enable_thread_queue_debug).c_str());
                
                log_info("config loaded \"[RUNTIME] queue_depth\" = \"%d\"", config->queue_depth);
                log_info("config loaded \"[RUNTIME] queue_eventloop_sleep_ms\" = \"%d\"", config->queue_eventloop_sleep_ms);
                

                // /* show current installed modules */
                // for(int i = 0; i < bot_module_N; i++) {
                //         log_info("config loaded \"[MODULE] %s", config->module[i]);
                // }
        }
        
        
        
}


int ini_load_config(const char *filename, struct ini_config* config)
{
        if (ini_parse(filename, parse_config_cb, config) < 0) {
                log_fatal("%s", "Can't load config.ini \n");
                ini_free_mem(config);
                return -1;
        }
        return 0;
}