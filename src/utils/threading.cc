// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "../headers/threading.h"
#include "../headers/int_helper.h"
#include "../../submodule/log.c-patched/src/log.h"
#include <cstdio>

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
                        (ring->queue_list + i)->need_join,
                        FadhilRiyanto::int_utils::int_helper::int2bool2str((ring->queue_list + i)->state).c_str());
        }
};