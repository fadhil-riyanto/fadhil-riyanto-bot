// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "headers/handler.h"
#include "headers/command_parser.h"
#include "headers/error.h"
#include <cstddef>
#include <cstdio>
#include <fmt/core.h>
#include <tgbot/tgbot.h>
#include "../submodule/log.c-patched/src/log.h"
#include "headers/string_helper.h"

/* module headers start */
// #include "bot_module/main/headers/_reg.h"
#include "bot_module/main/headers/start.h"
#include "bot_module/main/headers/help.h"
/* module headers end */

#include "bot_module/main/headers/help_cb.h"


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
        int ret = 0;

        /* main handler start */
      
        if (!res->command.compare("/start")) {
                start_command cmd_ctx;
                cmd_ctx.req(this->ctx, this->bot, this->msg, NULL, this->config);
                cmd_ctx.run();
        }
        if (!res->command.compare("/help")) {
                help_command cmd_ctx;
                cmd_ctx.req(this->ctx, this->bot, this->msg, NULL, this->config);
                cmd_ctx.run();
        }

        
        if (ret == 0) {
                if (this->config->enable_log_when_module_called) {
                        log_debug("successfully executed command %s", res->command.c_str());
                }
        }


}


/* this below is callback handler */

FadhilRiyanto::fadhil_riyanto_bot::cb_handler::cb_handler(TgBot::CallbackQuery::Ptr *callback, TgBot::Bot *bot, struct ini_config *config,
                        volatile std::sig_atomic_t *signal_status, struct ctx *ctx)
{
        this->callback = callback;
        this->bot = bot;
        this->config = config;
        this->signal_status = signal_status;
        this->ctx = ctx;

        this->handle_cb();
}

void FadhilRiyanto::fadhil_riyanto_bot::cb_handler::handle_cb()
{
        std::string command = FadhilRiyanto::string_utils::string_helper::split_n_index(
                (*this->callback)->data, 0);

        if (command == "help_cb") {
                help_cb help_cb;
                help_cb.req(this->ctx, this->bot, this->callback, NULL, config);
                help_cb.run();
        }


        printf("cmd: %s\n", command.c_str());
}