// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef BOT_MODULE_MAIN_H
#define BOT_MODULE_MAIN_H

#include "../../../headers/base_module.h"
#include "../../../headers/inih_parser.h"
#include <tgbot/tgbot.h>

namespace FadhilRiyanto::mod::command {

class start_command {
private:
        TgBot::Bot *bot;
        std::string value;
        TgBot::Message::Ptr msg;
        struct ini_config *config;
        struct ctx *ctx;

public:
        void call(TgBot::Bot *bot, std::string value, TgBot::Message::Ptr msg, struct ctx *ctx,
                        struct ini_config *config);
        int run_entry();
        int bind(struct ctx *ctx, struct ini_config *config);
};

} /* namespace */

#endif