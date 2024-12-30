#include "headers/intrin.h"
#include <cstddef>
#include <tgbot/types/ReplyParameters.h>

void intrin_command::req(struct ctx *ctx, TgBot::Bot *bot, TgBot::Message::Ptr *msg, TgBot::Api *api,
                struct ini_config *config) 
{
        this->ctx = ctx;
        this->bot = bot;
        this->api = api;
        this->msg = msg;
        this->config = config;
}

void intrin_command::run()
{
        TgBot::ReplyParameters::Ptr reply_param(new TgBot::ReplyParameters());
        reply_param->chatId = (*this->msg)->chat->id;
        reply_param->messageId = (*this->msg)->messageId;

        this->bot->getApi().sendMessage(
                (*this->msg)->chat->id, "intel intrinsics", 
                NULL,
                reply_param);
}