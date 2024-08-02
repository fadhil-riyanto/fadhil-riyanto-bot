// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <stdio.h>
#include <tgbot/tgbot.h>
#include "headers/inih_parser.h"
#include "headers/threading.h"
#include "../submodule/inih/ini.h"
#include "../submodule/log.c-patched/src/log.h"
#include "headers/bot.h"
#include "headers/command_parser.h"

FadhilRiyanto::fadhil_riyanto_bot::fadhil_riyanto_bot(struct ini_config* config) : bot(config->bot_token)
{
        this->config = config;
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_show_basic_config(void)
{
        log_info("bot_username: %s", this->bot.getApi().getMe()->username.c_str());
        
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_handle_message(TgBot::Message::Ptr *msg, 
        struct FadhilRiyanto::threading::queue_ring *ring)
{
        log_info("%d : %s", (*msg)->chat->id, (*msg)->text.c_str());

        struct string_utils::command_parser_config parse_config = {
                .command_prefix = this->config->command_prefix,
                .bot_username = this->config->bot_username
        };

        struct string_utils::command_parser_result parse_res;

        string_utils::command_parser parse((*msg)->text, &parse_config, &parse_res);
        
        try {
                parse.get_raw_command();
                parse.get_raw_value();
                parse.command_parser_debug(this->config->enable_command_debug_log);
        } catch (std::invalid_argument) {
                /* handle non command message here */
        }

        if (parse_res.my_turn) {
                
                FadhilRiyanto::threading::thread_queue::send_queue(ring, (*msg));
                FadhilRiyanto::threading::thread_helper::queue_debugger(10, ring);

                this->bot.getApi().sendMessage((*msg)->chat->id, "halo " + parse_res.value);
        }
        
        // 
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_eventloop(void)
{
        struct FadhilRiyanto::threading::queue_ring ring;
        FadhilRiyanto::threading::thread_queue::thread_queue_init(10, &ring);

        this->bot.getEvents().onAnyMessage([this, &ring](TgBot::Message::Ptr message) -> void {
                this->bot_handle_message(&message, &ring);
                
        });
        
        try {
                
                TgBot::TgLongPoll longPoll(this->bot);
                while (true) {
                        if (this->config->enable_pool_start_log == true) {
                                log_info("Long poll started");
                        }
                        
                        longPoll.start();
                }
        } catch (TgBot::TgException& e) {
                printf("error: %s\n", e.what());
        }
}

int main()
{
        struct ini_config config;

        if (ini_parse("config.ini", parse_config_cb, &config) < 0) {
                log_fatal("%s", "Can't load config.ini \n");
                ini_free_mem(&config);
                return -1;
        }

        log_set_quiet(!config.enable_all_log);
        ini_show_config(&config);

        FadhilRiyanto::fadhil_riyanto_bot fadhil_riyanto_bot(&config);
        fadhil_riyanto_bot.bot_show_basic_config();
        fadhil_riyanto_bot.bot_eventloop();

        ini_free_mem(&config);
        return 0;

}
