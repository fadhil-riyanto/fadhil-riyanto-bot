// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef BASE_MODULE_H
#define BASE_MODULE_H

#include "ctx.h"
#include <tgbot/tgbot.h>
#include <string>
#include "command_parser.h"

/* bot_module abstract class */

namespace FadhilRiyanto::mod {

class base_module {
private:
        TgBot::Bot *bot;
        TgBot::Message::Ptr msg;
        struct ini_config *config;
        struct ctx *ctx;
public:
        virtual int module_init(TgBot::Bot *bot, TgBot::Message::Ptr msg, 
                struct ini_config *config, struct ctx *ctx,
                struct FadhilRiyanto::string_utils::command_parser_result *res) = 0;

        /* return found or not */
        virtual int module_next(std::string input) = 0;
};

class base_command {
private:
        TgBot::Bot *bot;
        std::string value;
        TgBot::Message::Ptr msg;

        virtual void call(TgBot::Bot *bot, std::string value, TgBot::Message::Ptr msg) = 0;
        virtual void run_entry() = 0;
};


} /* namespace */

#endif