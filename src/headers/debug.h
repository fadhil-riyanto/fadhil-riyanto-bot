// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <tgbot/tgbot.h>
#include "../../submodule/log.c-patched/src/log.h"

#define DSHOW_ADDR(x)                   \
        log_debug("%p", &x);

std::string debug_cb(TgBot::CallbackQuery::Ptr *cb);

#endif