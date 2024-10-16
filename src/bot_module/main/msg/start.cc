// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "../headers/start.h"
#include "../../../headers/ctx.h"
#include "../../../headers/inih_parser.h"
#include "bson/bson.h"
#include <cstddef>


void FadhilRiyanto::mod::command::start_command::call(TgBot::Bot *bot, std::string value,
                TgBot::Message::Ptr msg, struct ctx *ctx, struct ini_config *config)
{
        this->bot = bot;
        this->value = value;
        this->msg = msg;
        this->ctx = ctx;
        this->config = config;
}

int FadhilRiyanto::mod::command::start_command::bind(struct ctx *ctx, struct ini_config *config)
{
        this->ctx = ctx;
        this->config = config;
        return -1;
}

static inline TgBot::InlineKeyboardMarkup::Ptr __gen_keyboard(void)
{
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup());
        std::vector<TgBot::InlineKeyboardButton::Ptr> row0;

        TgBot::InlineKeyboardButton::Ptr reportbug_button(new TgBot::InlineKeyboardButton());
        reportbug_button->text = "report bugs";
        reportbug_button->url = "https://t.me/fadhil_riyanto";

        TgBot::InlineKeyboardButton::Ptr help_button(new TgBot::InlineKeyboardButton());
        help_button->text = "help";
        help_button->callbackData = "cb_help";

        row0.push_back(reportbug_button);
        row0.push_back(help_button);
        keyboard->inlineKeyboard.push_back(row0);

        return keyboard;

}

// void FadhilRiyanto::mod::command::start_command::bind(struct ctx *ctx, struct ini_config *config)
// {
//         this->ctx = ctx;
//         this->config = config;
// }



int FadhilRiyanto::mod::command::start_command::run_entry()
{
        const bson_t *doc;
        /* this->bot->getApi().sendMessage(
                (*this->msg).chat->id, "start from module"); */;
        
        mongoc_collection_t *collection = mongoc_client_get_collection(
                this->ctx->mongodb_ctx, "test-db", "collection"
        );

        bson_t *query = bson_new(); /* empty query */
        mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);


        while (mongoc_cursor_next (cursor, &doc)) {
                char* str = bson_as_canonical_extended_json (doc, NULL);
                printf ("%s\n", str);
                bson_free (str);
        }

        bson_free(query);
        mongoc_collection_destroy(collection);
        mongoc_cursor_destroy(cursor);

        // FadhilRiyanto::db::key_value key_value;
        // key_value.bind((*this->ctx).mongodb_ctx);
        // key_value.dump_all();

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