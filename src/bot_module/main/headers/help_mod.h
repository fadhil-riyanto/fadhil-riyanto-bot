#ifndef HELP_MOD_H
#define HELP_MOD_H

#include <tgbot/types/InlineKeyboardMarkup.h>

class help_mod
{
public:
        static TgBot::InlineKeyboardMarkup::Ptr __gen_help_keyboard(void);
        static TgBot::InlineKeyboardMarkup::Ptr __gen_help_keyboard_back(void);
        
};

#endif