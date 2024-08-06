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

FadhilRiyanto::fadhil_riyanto_bot::handler::handler(TgBot::Message::Ptr *message, TgBot::Bot *bot, struct ini_config *config,
                        volatile std::sig_atomic_t *signal_status, struct ctx *ctx)
{
        this->msg = message;
        this->bot = bot;
        this->config = config;
        this->signal_status = signal_status;
        this->ctx = ctx;

        this->classify_input();
};

void FadhilRiyanto::fadhil_riyanto_bot::handler::classify_input(void)
{
        struct FadhilRiyanto::string_utils::command_parser_config parse_config = {
                .command_prefix = '/',
                .bot_username = "@fadhil_riyanto_bot"
        };

        try {
                struct FadhilRiyanto::string_utils::command_parser_result res;

                FadhilRiyanto::string_utils::command_parser parser((*this->msg)->text, &parse_config, &res);
             
                parser.get_raw_command();
                parser.get_raw_value();

                /* debug enable or not ? */
                parser.command_parser_debug(true);
       
        } catch (FadhilRiyanto::error::not_command) {
                this->handle_text();
        }
}


void FadhilRiyanto::fadhil_riyanto_bot::handler::handle_text(void)
{
        std::string res = fmt::format("your message is {}!\n", (*this->msg)->text);

        this->bot->getApi().sendMessage(
                (*this->msg)->chat->id,
                res
        );
}