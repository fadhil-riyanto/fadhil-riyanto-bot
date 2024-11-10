// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */
#include <tgbot/types/InlineKeyboardButton.h>
#include <tgbot/types/InlineKeyboardMarkup.h>
#include <vector>
#include "headers/help_mod.h"


TgBot::InlineKeyboardMarkup::Ptr help_mod::__gen_help_keyboard(void)
{
        /* will returned */
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup());

        /* array of inlinekeyboatdbutton */
        std::vector<TgBot::InlineKeyboardButton::Ptr> row0;

        TgBot::InlineKeyboardButton::Ptr mainbtn(new TgBot::InlineKeyboardButton());
        mainbtn->text = "Main menu";
        mainbtn->callbackData = "help_cb main";
        row0.push_back(mainbtn);

        TgBot::InlineKeyboardButton::Ptr group_command_btn(new TgBot::InlineKeyboardButton());
        group_command_btn->text = "Group command & admin";
        group_command_btn->callbackData = "help_cb group";
        row0.push_back(group_command_btn);

        keyboard->inlineKeyboard.push_back(row0);

        std::vector<TgBot::InlineKeyboardButton::Ptr> row1;

        TgBot::InlineKeyboardButton::Ptr animebtn(new TgBot::InlineKeyboardButton());
        animebtn->text = "Anime";
        animebtn->callbackData = "help_cb anime";
        row1.push_back(animebtn);

        keyboard->inlineKeyboard.push_back(row1);

        return keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr help_mod::__gen_help_keyboard_back()
{
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup());

        std::vector<TgBot::InlineKeyboardButton::Ptr> row0;

        TgBot::InlineKeyboardButton::Ptr back_btn(new TgBot::InlineKeyboardButton());
        back_btn->text = "back";
        back_btn->callbackData = "help_cb back";
        row0.push_back(back_btn);
        
        keyboard->inlineKeyboard.push_back(row0);

        return keyboard;
}