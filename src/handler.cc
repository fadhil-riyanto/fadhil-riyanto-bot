// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "headers/handler.h"

FadhilRiyanto::handler::handler(TgBot::Message::Ptr *message, TgBot::Bot *bot, struct ini_config *config,
                        volatile std::sig_atomic_t *signal_status, struct ctx *ctx)
{
        this->message = message;
        this->bot = bot;
        this->config = config;
        this->signal_status = signal_status;
        this->ctx = ctx
}