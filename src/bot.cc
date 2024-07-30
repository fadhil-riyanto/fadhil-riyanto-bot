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
#include "headers/bot.h"

FadhilRiyanto::fadhil_riyanto_bot::fadhil_riyanto_bot(const std::string bot_token) : bot(bot_token)
{
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_show_basic_config(void)
{
        printf("bot_username: %s\n", this->bot.getApi().getMe()->username.c_str());
        
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_eventloop(void)
{
        
        try {
                
                TgBot::TgLongPoll longPoll(bot);
                while (true) {
                        printf("Long poll started\n");
                        longPoll.start();
                }
        } catch (TgBot::TgException& e) {
                printf("error: %s\n", e.what());
        }
}

int main()
{
        struct ini_config config;

        if (ini_parse("config.ini", parse_config_cb, &config)) {
                // printf("%s", "Can't load config.ini \n");
        }

        FadhilRiyanto::fadhil_riyanto_bot fadhil_riyanto_bot(config.bot_token);
        fadhil_riyanto_bot.bot_show_basic_config();
        fadhil_riyanto_bot.bot_eventloop();

        free(config.bot_token);
        return 0;

}

// int _main() {
//         /* start reading ini. */
//         struct ini_config config;

//         if (ini_parse("config.ini", parse_config_cb, &config)) {
//                 // printf("%s", "Can't load config.ini \n");
//         }

//         TgBot::Bot bot(config.bot_token);

//         bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
//                 bot.getApi().sendMessage(message->chat->id, "Hi!");
//         });

//         bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
//                 printf("User wrote %s\n", message->text.c_str());
//                 if (StringTools::startsWith(message->text, "/start")) {
//                 return;
//                 }
//                 bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
//         });
        
//         try {
//                 printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
//                 TgBot::TgLongPoll longPoll(bot);
//                 while (true) {
//                         printf("Long poll started\n");
//                         longPoll.start();
//                 }
//         } catch (TgBot::TgException& e) {
//                 printf("error: %s\n", e.what());
//         }


//         free(config.bot_token);

//         return 0;
// }