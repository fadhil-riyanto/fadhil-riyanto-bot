// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "headers/handler.h"
#include "headers/command_parser.h"
#include "headers/error.h"
#include <fmt/core.h>
#include <tgbot/tgbot.h>

void FadhilRiyanto::handler::recv_from_thqueue(TgBot::Message::Ptr *message, TgBot::Bot *bot, struct ini_config *config,
                        volatile std::sig_atomic_t *signal_status, struct ctx *ctx)
{
        this->msg = message;
        this->bot = bot;
        this->config = config;
        this->signal_status = signal_status;
        this->ctx = ctx;
};

void FadhilRiyanto::handler::classify_input(void)
{
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
        } catch (FadhilRiyanto::error::not_command) {
                /* handle non command message here */
                /* call normal text handler */

                this->handle_text();

        }

        if (parse_res.my_turn) {
                
                this->handle_command_input();

                // this->bot.getApi().sendMessage((*msg)->chat->id, "halo " + parse_res.value);
        }
}

void FadhilRiyanto::handler::handle_text()
{
        std::string res = fmt::format("your message is {}!\n", (*this->msg)->text);

        this->bot->getApi().sendMessage(
                (*this->msg)->chat->id,
                res
        );
}