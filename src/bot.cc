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
#include "headers/inih_parser.h"
#include "headers/threading.h"
#include "../submodule/log.c-patched/src/log.h"
#include "headers/bot.h"
#include "headers/ctx.h"
#include "headers/debug.h"

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
        volatile std::sig_atomic_t *signal_status, struct ctx *ctx) : bot(config->bot_token, "http://127.0.0.1:8081")
{
        this->ctx = ctx;
        this->config = config;
        this->signal_status = signal_status;
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_show_basic_config(void)
{
        log_info("bot_username: %s", this->bot.getApi().getMe()->username.c_str());
        
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_handle_message(TgBot::Message::Ptr *msg, 
        struct FadhilRiyanto::threading::queue_ring *ring)
{
        bool ret;

        log_info("%d : %s", (*msg)->chat->id, (*msg)->text.c_str());
        
        ret = FadhilRiyanto::threading::thread_queue::send_queue(ring, (*msg));
        if (ret == false) {
                this->bot_handle_queue_overflow(msg);
        }
        FadhilRiyanto::threading::thread_helper::queue_debugger(this->config->queue_depth, ring, this->config);


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

        this->bot.getApi().sendMessage(
                (*msg)->chat->id, 
                "server overloaded, try increasing 'queue_depth' at config.ini runtime section",
                nullptr, 
                replyParam
        );
}

void FadhilRiyanto::fadhil_riyanto_bot::bot_handle_callbackquery(TgBot::CallbackQuery::Ptr *cb,
                struct FadhilRiyanto::threading::queue_ring *ring)
{
        log_info((*cb)->data.c_str());
}

// void FadhilRiyanto::fadhil_riyanto_bot::bot_run_cleanup(int sigint)
// {
//         /* call on sigint signal */
//         log_warn("got SIGINT, exitting ...");
//         global_signal_status = SIGINT;
// }




int main()
{
        std::signal(SIGINT, signal_handler);
        struct ini_config config;


        // struct FadhilRiyanto::dlsys::loaded_libs loaded_libs;
        

        // if (ini_parse("config.ini", parse_config_cb, &config) < 0) {
        //         log_fatal("%s", "Can't load config.ini \n");
        //         ini_free_mem(&config);
        //         return -1;
        // }
        ini_load_config("config.ini", &config);

        log_set_quiet(!config.enable_all_log);
        ini_show_config(&config);

        /* initializer reserved space here */
        struct ctx ctx;
        ctx.reserved = 10;
        DSHOW_ADDR(ctx.reserved);

        // FadhilRiyanto::dlsys::shared_lib_loader::config_module_load(
        //         config.module, 
        //         &loaded_libs, 
        //         bot_module_N
        // );
        // TgBot::CurlHttpClient curlHttpClient;
        

        FadhilRiyanto::fadhil_riyanto_bot fadhil_riyanto_bot(&config, &global_signal_status, &ctx);
        
        try {
                /* devnote: remove */
                fadhil_riyanto_bot.bot_show_basic_config();
                fadhil_riyanto_bot.bot_eventloop();
        } catch (boost::wrapexcept<boost::system::system_error> e) {
                log_fatal("network error %s", e.what());
        }
        

        // FadhilRiyanto::dlsys::shared_lib_loader::close_all_lib(&loaded_libs);

        ini_free_mem(&config);
        return 0;

}
