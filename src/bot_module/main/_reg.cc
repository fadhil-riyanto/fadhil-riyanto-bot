// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "../../headers/command_parser.h"
#include "../../headers/debug.h"
#include "../../headers/ctx.h"
#include <tgbot/tgbot.h>
#include <string>
#include <fmt/core.h>
#include <stdio.h>

/* local */
#include "headers/_reg.h"
#include "headers/start.h"

int module_main::module_init(TgBot::Bot *bot, TgBot::Message::Ptr msg, 
                                struct ini_config *config, struct ctx *ctx,
                                struct FadhilRiyanto::string_utils::command_parser_result *res)
{
        this->bot = bot;
        this->msg = msg;
        this->config = config;
        this->ctx = ctx;
        
        this->module_next(res->command);
        return 0; /* temp return */
}

int module_main::module_next(std::string input)
{
        DSHOW_ADDR(this->ctx->reserved);
        printf("module called \"%s\"\n", input.c_str());

        if (!input.compare("/start")) {
                // fmt::print("command called\n");
                FadhilRiyanto::mod::command::start_command start_command;
                start_command.call(this->bot, "ini input", this->msg);
                start_command.run_entry();
        }

        return 0;
}