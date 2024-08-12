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

static inline TgBot::InlineKeyboardMarkup::Ptr __gen_keyboard(void)
{
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        std::vector<TgBot::InlineKeyboardButton::Ptr> row0;

        TgBot::InlineKeyboardButton::Ptr reportbug_button(new TgBot::InlineKeyboardButton);
        reportbug_button->text = "report bugs";
        reportbug_button->url = "https://t.me/fadhil_riyanto";

        TgBot::InlineKeyboardButton::Ptr help_button(new TgBot::InlineKeyboardButton);
        help_button->text = "help";
        help_button->callbackData = "cb_help";

        row0.push_back(reportbug_button);
        row0.push_back(help_button);
        keyboard->inlineKeyboard.push_back(row0);

        return keyboard;

}

int FadhilRiyanto::mod::command::start_command::run_entry()
{
        /* this->bot->getApi().sendMessage(
                (*this->msg).chat->id, "start from module"); */

        TgBot::ReplyParameters::Ptr replyParam(new TgBot::ReplyParameters());
        
        replyParam->messageId = (*this->msg).messageId;
        replyParam->chatId = (*this->msg).chat->id;

        std::string replytext = "Hey there! My name is Fadhil.\n" \
                                "I can managing your group with useful features";

        this->bot->getApi().sendMessage(
                (*this->msg).chat->id, 
                replytext,
                nullptr, 
                replyParam,
                __gen_keyboard()
        );

        /* return 0 is must */
        return 0;
}