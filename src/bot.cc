// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <stdio.h>
#include <tgbot/tgbot.h>
#include "headers/inih_parser.h"
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

void FadhilRiyanto::fadhil_riyanto_bot::bot_handle_message(TgBot::Message::Ptr *msg)
{
        log_info("%d : %s", (*msg)->chat->id, (*msg)->text.c_str());
        // this->bot.getApi().sendMessage((*msg)->chat->id, "string: " + (*msg)->text);
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_eventloop(void)
{

        this->bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr message) -> void {
                this->bot_handle_message(&message);
        });
        
        try {
                
                TgBot::TgLongPoll longPoll(this->bot);
                while (true) {
                        log_info("Long poll started");
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

        log_set_quiet(config.logger);
        ini_show_config(&config);

        FadhilRiyanto::fadhil_riyanto_bot fadhil_riyanto_bot(&config);
        fadhil_riyanto_bot.bot_show_basic_config();
        fadhil_riyanto_bot.bot_eventloop();

        ini_free_mem(&config);
        return 0;

}
