// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef BOT_MODULE_UTILS_START
#define BOT_MODULE_UTILS_START

#include "../../../headers/base_module.h"
#include <tgbot/tgbot.h>

namespace FadhilRiyanto::mod::command {

class start_command : public base_command {
private:
        TgBot::Bot *bot;
        std::string value;
        TgBot::Message::Ptr msg;
public:
        void call(TgBot::Bot *bot, std::string value, TgBot::Message::Ptr msg);
        void run_entry();
};

} /* namespace */

#endif