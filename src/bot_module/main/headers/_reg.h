// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef _MAIN_REG_H
#define _MAIN_REG_H

#include "../../../headers/command_parser.h"
#include "../../../headers/base_module.h"
#include "../../../headers/ctx.h"
#include <tgbot/tgbot.h>
#include <string>
#include <fmt/core.h>

class module_main : public FadhilRiyanto::mod::base_module {
        TgBot::Bot *bot;
        TgBot::Message::Ptr msg;
        struct ini_config *config;
        struct ctx *ctx;
public:
        int module_init(TgBot::Bot *bot, TgBot::Message::Ptr msg, 
                                        struct ini_config *config, struct ctx *ctx,
                                        struct FadhilRiyanto::string_utils::command_parser_result *res);

        int module_next(std::string input);
};

#endif