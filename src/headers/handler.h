// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef HANDLER_H
#define HANDLER_H

#include <tgbot/tgbot.h>
#include "inih_parser.h"
#include "ctx.h"
#include <csignal>

namespace FadhilRiyanto {

class handler {
private:
        TgBot::Message::Ptr *msg;
        TgBot::Bot *bot;
        struct ini_config *config;
        volatile std::sig_atomic_t *signal_status;
        struct ctx *ctx;
        void classify_input(void);

public:
        void recv_from_thqueue(TgBot::Message::Ptr *message, TgBot::Bot *bot, struct ini_config *config,
                        volatile std::sig_atomic_t *signal_status, struct ctx *ctx);
        void handle_command_input();
        void handle_text();
};


} /* namespace */

#endif