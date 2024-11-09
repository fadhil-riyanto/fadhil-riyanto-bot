#include "headers/help.h"
#include "headers/help_mod.h"

void help_command::req(struct ctx *ctx, TgBot::Bot *bot, TgBot::Message::Ptr *msg, TgBot::Api *api,
                struct ini_config *config)
{
        this->ctx = ctx;
        this->bot = bot;
        this->api = api;
        this->msg = msg;
        this->config = config;
}

void help_command::run(void)
{
        this->bot->getApi().sendMessage(
                (*this->msg)->chat->id, "help menu", 
                nullptr, nullptr, 
                help_mod::__gen_help_keyboard());
}