// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "headers/start.h"

void FadhilRiyanto::mod::command::start_command::call(TgBot::Bot *bot, std::string value,
                                                        TgBot::Message::Ptr msg)
{
        this->bot = bot;
        this->value = value;
        this->msg = msg;
}

int FadhilRiyanto::mod::command::start_command::run_entry()
{
        this->bot->getApi().sendMessage(
                (*this->msg).chat->id, "start from module");

        /* return 0 is must */
        return 0;
}