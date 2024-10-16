// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "../../headers/command_parser.h"
#include "../../headers/ctx.h"
#include "../../headers/inih_parser.h"
#include <tgbot/tgbot.h>
#include <string>
#include <fmt/core.h>

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
        this->config = config;
        
        return this->module_next(res->command);
}

int module_main::module_next(std::string input)
{
        if (!input.compare("/start")) {
                // fmt::print("command called\n");
                FadhilRiyanto::mod::command::start_command start_command;
                int a = 9;
                int b = 2;

                start_command.call(this->bot, "temp val", this->msg, this->ctx, this->config);
                // start_command.call(this->bot, "ini input", this->msg, this->ctx, this->config);
                // start_command.bind(this->ctx, this->config);
                return start_command.run_entry();
        }

        // if (!input.compare("/startd")) {
        //         // fmt::print("command called\n");
        //         FadhilRiyanto::mod::command::startd_command startd_command;
        //         startd_command.call(this->bot, "ini input", this->msg);
        //         return startd_command.run_entry();
        // }

        return -1;
}