// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "headers/handler.h"
#include "headers/command_parser.h"
#include "headers/error.h"
#include <cstdio>
#include <fmt/core.h>
#include <tgbot/tgbot.h>

/* module headers start */
#include "bot_module/main/headers/_reg.h"
/* module headers end */

FadhilRiyanto::fadhil_riyanto_bot::handler::handler(TgBot::Message::Ptr *message, 
                TgBot::Bot *bot, struct ini_config *config,
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
        // struct FadhilRiyanto::string_utils::command_parser_result res;

        struct FadhilRiyanto::string_utils::command_parser_config parse_config = {
                .command_prefix = '/',
                .bot_username = "@fadhil_riyanto_bot"
        };

        try {
                
                FadhilRiyanto::string_utils::command_parser parser((*this->msg)->text, &parse_config, &this->res);
             
                parser.get_raw_command();
                parser.get_raw_value();

                /* debug enable or not ? */
                parser.command_parser_debug(this->config->enable_command_debug_log);
       
        } catch (FadhilRiyanto::error::not_command) {
                this->handle_text();
        }

        if (res.my_turn) {
                this->handle_command_input(&res);
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

void FadhilRiyanto::fadhil_riyanto_bot::handler::handle_command_input(
        struct FadhilRiyanto::string_utils::command_parser_result *res
)
{
        /* main handler start */
        module_main module_main;
        module_main.module_init(
                this->bot, 
                (*this->msg), 
                this->config, 
                this->ctx,
                &this->res
        );


}