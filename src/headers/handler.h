// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef HANDLER_H
#define HANDLER_H

#include "command_parser.h"
#include <tgbot/Bot.h>
#include <tgbot/tgbot.h>
#include "inih_parser.h"
#include "ctx.h"
#include <csignal>
#include <tgbot/types/CallbackQuery.h>


namespace FadhilRiyanto::fadhil_riyanto_bot {

class handler {
private:
        TgBot::Message::Ptr *msg;
        TgBot::Bot *bot;
        struct ini_config *config;
        volatile std::sig_atomic_t *signal_status;
        struct ctx *ctx;
        struct FadhilRiyanto::string_utils::command_parser_result res;

        void classify_input(void);

public:
        handler(TgBot::Message::Ptr *message, TgBot::Bot *bot, struct ini_config *config,
                        volatile std::sig_atomic_t *signal_status, struct ctx *ctx);
        void handle_command_input(struct FadhilRiyanto::string_utils::command_parser_result *res);
        void handle_text();
};

class cb_handler
{
        TgBot::CallbackQuery::Ptr *callback;
        TgBot::Bot *bot;
        struct ini_config *config;
        volatile std::sig_atomic_t *signal_status;
        struct ctx *ctx;

public:
        cb_handler(TgBot::CallbackQuery::Ptr *callback, TgBot::Bot *bot, struct ini_config *config,
                        volatile std::sig_atomic_t *signal_status, struct ctx *ctx);

private:
        void handle_cb();
};

// class 


} /* namespace */

#endif