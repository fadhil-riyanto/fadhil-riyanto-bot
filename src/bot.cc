// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <csignal>
#include <cstddef>
#include <fmt/core.h>
#include <stdio.h>
#include <tgbot/net/HttpClient.h>
#include <tgbot/tgbot.h>
#include <tgbot/types/ReplyParameters.h>
#include <tgbot/net/CurlHttpClient.h>
#include <tgbot/Api.h>
#include "headers/inih_parser.h"
#include "headers/key_value.h"
#include "headers/threading.h"
#include "../submodule/log.c-patched/src/log.h"
#include "headers/bot.h"
#include "headers/ctx.h"
#include "headers/debug.h"

#define DEVENV
#define HAVE_CURL

namespace
{
        volatile std::sig_atomic_t global_signal_status;
}


void signal_handler(int signal)
{
        global_signal_status = signal;
        log_info("got sigint");
}


FadhilRiyanto::fadhil_riyanto_bot::fadhil_riyanto_bot(struct ini_config* config, 
        volatile std::sig_atomic_t *signal_status, struct ctx *ctx, TgBot::CurlHttpClient *api_http) 
        : 
        #ifdef SERVER_ENV
        bot(config->bot_token, "https://api.telegram.org"),
        api(config->bot_token, *api_http,  "https://api.telegram.org")
        #else 
        bot(config->bot_token, "http://127.0.0.1:8081"),
        api(config->bot_token, *api_http,  "http://127.0.0.1:8081")
        #endif
        
{
        // TgBot::CurlHttpClient curlhttpclient;

        // TgBot::Api 

        // this->api = api;
        this->ctx = ctx;
        this->config = config;
        this->signal_status = signal_status;
        DSHOW_ADDR(this->ctx);
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_show_basic_config(void)
{
        log_info("bot_username: %s", this->bot.getApi().getMe()
                                                ->username.c_str());
        log_info("mongodb_uri: %s", this->config->mongodb_conn_string);
        
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_handle_message(TgBot::Message::Ptr *msg, 
        struct FadhilRiyanto::threading::queue_ring *ring)
{
        bool ret;

        log_info("%ld : %s", (*msg)->chat->id, (*msg)->text.c_str());
        
        ret = FadhilRiyanto::threading::thread_queue::send_queue(ring, (*msg));
        if (ret == false) {
                this->bot_handle_queue_overflow(msg);
        }
        FadhilRiyanto::threading::thread_helper::queue_debugger(
                                this->config->queue_depth, 
                                ring, 
                                this->config
        );


}

void FadhilRiyanto::fadhil_riyanto_bot::bot_eventloop(void)
{
        struct FadhilRiyanto::threading::queue_ring ring;
        FadhilRiyanto::threading::thread_queue::thread_queue_init(
                this->config->queue_depth, &ring
        );
        

        FadhilRiyanto::threading::thread_queue_runner th_queue_runner;
        th_queue_runner.thread_queue_runner_link(
                &ring, 
                this->signal_status, 
                &this->bot, 
                this->config,
                this->ctx
        );
        
        
        th_queue_runner.create_child_eventloop();

        this->bot.getEvents().onAnyMessage([this, &ring](TgBot::Message::Ptr message) -> void {
                this->bot_handle_message(&message, &ring);
        });

        this->bot.getEvents().onCallbackQuery([this, &ring](TgBot::CallbackQuery::Ptr query) -> void {
                this->bot_handle_callbackquery(&query, &ring);
        });

        this->signal_status = &global_signal_status;
        
        try {
                
                TgBot::TgLongPoll longPoll(this->bot);
                while (true && *this->signal_status != SIGINT) {
                        if (this->config->enable_pool_start_log == true) {
                                log_info("Long poll started");
                        }
                        
                        longPoll.start();
                }
        } catch (TgBot::TgException& e) {
                printf("error: %s\n", e.what());
        }
        
        th_queue_runner.thread_queue_cleanup();
        FadhilRiyanto::threading::thread_queue::thread_queue_destroy(&ring);
}

/* note: vg_err uninitialized value L109 */
void FadhilRiyanto::fadhil_riyanto_bot::bot_handle_queue_overflow(TgBot::Message::Ptr *msg = NULL)
{       
        TgBot::ReplyParameters *ctxptr = new TgBot::ReplyParameters();
        TgBot::ReplyParameters::Ptr replyParam(ctxptr);
        
        replyParam->messageId = (*msg)->messageId;
        replyParam->chatId = (*msg)->chat->id;

        int is_group = (*msg)->chat->type == TgBot::Chat::Type::Supergroup ? 1 : 0;

        if (!is_group) {
                this->bot.getApi().sendMessage(
                        (*msg)->chat->id, 
                        "server overloaded, try increasing 'queue_depth' at config.ini runtime section",
                        nullptr, 
                        replyParam
                );
        }
        
}

/* note: vg_err uninitialized value L109 */
void FadhilRiyanto::fadhil_riyanto_bot::bot_handle_queue_overflow_cb(TgBot::CallbackQuery::Ptr *cb = NULL)
{       
        // bool result = TgBot::Api::answerCallbackQuery()
                
        // )

        printf("%s\n", (*cb)->id.c_str());


        
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_handle_callbackquery(TgBot::CallbackQuery::Ptr *cb,
                struct FadhilRiyanto::threading::queue_ring *ring)
{
        bool ret;

        // TgBot::Api::answerCallbackQuery(
        //         (*cb)->id,
        //         "test cb",
        //         1,
        //         "",
        //         1
        // );

        ret = FadhilRiyanto::threading::thread_queue::send_cb_queue(ring, (*cb));
        if (ret == false) {
                this->bot_handle_queue_overflow_cb(cb);
        }
}

static int check_config_exist_or_die(struct ini_config *config) 
{
        #ifdef DEVENV
        if (access("config.ini", F_OK) == 0) {
                ini_load_config("config.ini", config);
        #else
        if (access("/etc/fadhil-riyanto-bot/config.ini", F_OK) == 0) {
                ini_load_config("/etc/fadhil-riyanto-bot/config.ini", config);
        #endif
                return 0;
        } else {
                return -1;
        }

}

int main()
{
        std::signal(SIGINT, signal_handler);
        struct ini_config config;
        

        if (check_config_exist_or_die(&config) == -1) {
                return -1;
        }

        mongoc_init();
        curl_global_init(CURL_GLOBAL_ALL);

        log_set_quiet(!config.enable_all_log);
        ini_show_config(&config);

        /* init reserved space here */
        struct ctx ctx;
        ctx.reserved = 10;
        ctx.mongodb_ctx = mongoc_client_new(config.mongodb_conn_string);

        if (ctx.mongodb_ctx == NULL) {
                printf("mongodb failed connect\n");
        }

        /* test, and use data from ctx */
        FadhilRiyanto::db::key_value key_value(ctx.mongodb_ctx, &config);

        

        key_value.set("test", "test 2");

        TgBot::CurlHttpClient curlhttpclient;

        FadhilRiyanto::fadhil_riyanto_bot fadhil_riyanto_bot(&config, &global_signal_status, &ctx, &curlhttpclient);
        
        try {
                fadhil_riyanto_bot.bot_show_basic_config();
                fadhil_riyanto_bot.bot_eventloop();
        } catch (boost::wrapexcept<boost::system::system_error> e) {
                log_fatal("network error %s", e.what());
        }
        
        /* free current resource */

        mongoc_client_destroy(ctx.mongodb_ctx);
        mongoc_cleanup();
        curl_global_cleanup();

        ini_free_mem(&config);
        return 0;

}
