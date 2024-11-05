#include "headers/start.h"
#include <tgbot/types/InlineKeyboardButton.h>
#include <tgbot/types/InlineKeyboardMarkup.h>
#include <vector>

static inline TgBot::InlineKeyboardMarkup::Ptr __gen_keyboard(void)
{
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup());
        std::vector<TgBot::InlineKeyboardButton::Ptr> row0;

        TgBot::InlineKeyboardButton::Ptr reportbtn(new TgBot::InlineKeyboardButton());
        reportbtn->text = "report bugs";
        reportbtn->url = "https://t.me/fadhil_riyanto";
        row0.push_back(reportbtn);

        TgBot::InlineKeyboardButton::Ptr help_button(new TgBot::InlineKeyboardButton());
        help_button->text = "help";
        help_button->callbackData = "cb_help";
        row0.push_back(help_button);

        keyboard->inlineKeyboard.push_back(row0);

        return keyboard;

        
}

void start_command::req(struct ctx *ctx, TgBot::Bot *bot, TgBot::Message::Ptr *msg, 
                TgBot::Api *api, struct ini_config *config)
{
        this->ctx = ctx;
        this->bot = bot;
        this->api = api;
        this->msg = msg;
        this->config = config;
}


void start_command::run(void)
{

        TgBot::ReplyParameters::Ptr replyParam(new TgBot::ReplyParameters());

        std::string replytext = "Hey there! My name is Fadhil.\n" \
                                "I can managing your group with useful features";

        this->bot->getApi().sendMessage(
                (*this->msg)->chat->id, 
                replytext,
                nullptr, nullptr, __gen_keyboard()
        );

}
