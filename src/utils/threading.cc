// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "../headers/threading.h"
#include "../headers/int_helper.h"
#include "../../submodule/log.c-patched/src/log.h"
#include <csignal>
#include <cstdio>
#include <thread>
#include <chrono>
#include <fmt/core.h>

void FadhilRiyanto::threading::thread_queue::thread_queue_init(int depth, struct queue_ring *ring)
{
        ring->queue_list = new struct message_queue_data[depth];
        ring->depth = depth;
        for(int i = 0; i < depth; i++) {
                (ring->queue_list + i)->need_join = false;
                (ring->queue_list + i)->state = false;
                (ring->queue_list + i)->queue_num = -1;
        }

        /* init counter */
        ring->counter = 0;
        
};

void FadhilRiyanto::threading::thread_queue::thread_queue_destroy(struct queue_ring *ring)
{
        delete [] ring->queue_list;
        
};

bool FadhilRiyanto::threading::thread_queue::send_queue(struct queue_ring *ring, TgBot::Message::Ptr message)
{
        for(int i = 0; i < ring->depth; i++) {
                if ((ring->queue_list + i)->need_join == 0 && (ring->queue_list + i)->state == 0 &&
                        (ring->queue_list + i)->queue_num == -1) {

                        /* set current state to ring */
                        (ring->queue_list + i)->data = message;
                        (ring->queue_list + i)->need_join = false;
                        (ring->queue_list + i)->queue_num = ring->counter;
                        (ring->queue_list + i)->state = true;

                        ring->counter = ring->counter + 1;

                        return true;
                }
        }

        return false;
}


void FadhilRiyanto::threading::thread_helper::queue_debugger(int depth, struct queue_ring *ring)
{
        log_info("checking all worker");
        for(int i = 0; i < depth; i++) {
                log_debug("qw %d | need_join %s, queue_num %d, state %s", i, 
                        FadhilRiyanto::int_utils::int_helper::int2bool2str((ring->queue_list + i)->need_join).c_str(),
                        (ring->queue_list + i)->queue_num,
                        FadhilRiyanto::int_utils::int_helper::int2bool2str((ring->queue_list + i)->state).c_str());
        }
};

void FadhilRiyanto::threading::thread_queue_runner::thread_queue_runner_link(struct queue_ring *ring,
        volatile std::sig_atomic_t *signal_handler, TgBot::Bot *bot)
{
        this->ring = ring;
        this->signal_handler = signal_handler;
        this->bot = bot;
}

// void FadhilRiyanto::threading::create_event_loop()
// {
//         // while(this->signal_handler == 1)
// }
void FadhilRiyanto::threading::thread_queue_runner::process_msg(int counter_idx, 
                TgBot::Bot *bot, TgBot::Message::Ptr msg, 
                struct queue_ring *ring, volatile std::sig_atomic_t *signal_handler)
{

        std::string res = fmt::format("your message {}!\n", msg->text);

        bot->getApi().sendMessage(
                msg->chat->id,
                res
        );

        (ring->queue_list + counter_idx)->need_join = 1;
        (ring->queue_list + counter_idx)->state = 0;
}

void FadhilRiyanto::threading::thread_queue_runner::eventloop_th_setup_state(int counter_idx, 
                                                TgBot::Bot *bot, TgBot::Message::Ptr msg, 
                                                struct queue_ring *ring, volatile std::sig_atomic_t *signal_handler)
{
        /* setup state */

        (ring->queue_list + counter_idx)->state = 1;
        (ring->queue_list + counter_idx)->need_join = 0;
        

        (ring->queue_list + counter_idx)->handler_th = std::thread(
                FadhilRiyanto::threading::thread_queue_runner::process_msg, 
                        counter_idx, bot, msg, ring, signal_handler
        );
}

void FadhilRiyanto::threading::thread_queue_runner::eventloop(struct queue_ring *ring, 
                        volatile std::sig_atomic_t *signal_handler, TgBot::Bot *bot)
{
        long seen_largest = 0;
        
        log_debug("completion queue thread created");

        while(true && *signal_handler != SIGINT) {
                for(int i = 0; i < ring->depth; i++) {
                        if ((ring->queue_list + i)->queue_num == seen_largest) {
                                log_debug("create thread %lu", i);

                                FadhilRiyanto::threading::thread_queue_runner::eventloop_th_setup_state(
                                        i, bot, (ring->queue_list + i)->data, ring, signal_handler
                                );
                                // this->bot.getApi().sendMessage((*msg)->chat->id, "halo " + parse_res.value);
                                // std::thread runner
                                
                                // std::thread ->
                                

                                

                                seen_largest++;
                        }
                }

                /* check thread state */
                FadhilRiyanto::threading::thread_queue_runner::thread_zombie_cleaner(ring, signal_handler);

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
}

void FadhilRiyanto::threading::thread_queue_runner::create_child_eventloop()
{
        /* init our separated thread */
        log_debug("creating thread ...");
        this->initializer_thread = std::thread(this->eventloop, this->ring, this->signal_handler, this->bot);
        // std::thread initializer(this->eventloop, this->ring, this->signal_handler, this->bot);
        // return initializer;
}

void FadhilRiyanto::threading::thread_queue_runner::thread_zombie_cleaner(struct queue_ring *ring,
                                                                        volatile std::sig_atomic_t *signal_handler)
{
        for(int i = 0; i < ring->depth; i++) {
                if ((ring->queue_list + i)->need_join == 1 && *signal_handler != SIGINT) {
                        (ring->queue_list + i)->handler_th.join();
                        (ring->queue_list + i)->need_join = 0;
                        (ring->queue_list + i)->queue_num = -1;
                        log_info("joined thread %d with queue_num %d", i, (ring->queue_list + i)->queue_num);
                }
        }
        
}

void FadhilRiyanto::threading::thread_queue_runner::thread_queue_cleanup()
{
        
        log_info("entering");
do_again:
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        int counter = 0;
        for(int i = 0; i < ring->depth; i++) {
                log_info("check");
                if ((ring->queue_list + i)->state != 1)
                        counter++;
                
        }
        if (counter == ring->depth)
                goto next;

        /* bugnote: jump with counter reset */
        else
                goto do_again;
next:
        log_info("[EXIT] all thread is dead");

        for(int i = 0; i < ring->depth; i++) {
                if ((ring->queue_list + i)->need_join == 1) {
                        (ring->queue_list + i)->handler_th.join();
                        (ring->queue_list + i)->need_join = 0;
                        (ring->queue_list + i)->queue_num = -1;
                        log_info("[EXIT] joined thread %d with queue_num %d", i, (ring->queue_list + i)->queue_num);
                }
        }
        
        this->initializer_thread.join();

}