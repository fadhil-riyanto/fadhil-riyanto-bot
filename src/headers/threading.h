// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef THREADING_H
#define THREADING_H

#include <csignal>
#include <tgbot/tgbot.h>
#include <thread>
#include "inih_parser.h"
#include "ctx.h"

namespace FadhilRiyanto::threading {

struct message_queue_data {
        TgBot::Message::Ptr data;
        std::thread handler_th;

        /* unique number assigned each queue */
        long queue_num;

        /* true if alive */
        bool state;

        /* true before cleaned by eventloop thread join */
        bool need_join;
};

struct queue_ring
{
        struct message_queue_data *queue_list;
        int current_size;
        int depth;

         /* do not touch */
        long counter;
};

class thread_helper {
public:
        static void queue_debugger(int depth, struct queue_ring *ring, struct ini_config *config);
};

class thread_queue {
public:
        static void thread_queue_init(int depth, struct queue_ring *ring);
        static bool send_queue(struct queue_ring *ring, TgBot::Message::Ptr message);
        static void thread_queue_destroy(struct queue_ring *ring);
};

class thread_queue_runner {
private:
        struct queue_ring *ring;
        volatile std::sig_atomic_t *signal_handler;
        TgBot::Bot *bot;
        struct ini_config *config;
        struct ctx *ctx;

        std::thread initializer_thread;

        static void thread_zombie_cleaner(struct queue_ring *ring, volatile std::sig_atomic_t *signal_handler,
                                                struct ini_config *config);
        static void eventloop(struct queue_ring *ring, volatile std::sig_atomic_t *signal_handler, TgBot::Bot *bot,
                                struct ini_config *config, struct ctx *ctx);
        static void process_msg(int counter_idx, TgBot::Bot *bot, TgBot::Message::Ptr msg, 
                                struct queue_ring *ring, volatile std::sig_atomic_t *signal_handler, 
                                struct ini_config *config, struct ctx *ctx);
        static void eventloop_th_setup_state(int counter_idx, TgBot::Bot *bot, TgBot::Message::Ptr msg, 
                                                struct queue_ring *ring, volatile std::sig_atomic_t *signal_handler,
                                                struct ini_config *config, struct ctx *ctx);
public:
        void thread_queue_runner_link(struct queue_ring *ring, volatile std::sig_atomic_t *signal_handler,
                TgBot::Bot *bot, struct ini_config *config, struct ctx *ctx);
        void create_child_eventloop();
        void thread_queue_cleanup();
};

}


#endif
