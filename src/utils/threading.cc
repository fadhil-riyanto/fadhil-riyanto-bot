// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "../headers/threading.h"
#include "../../submodule/log.c-patched/src/log.h"
#include <cstdio>

FadhilRiyanto::threading::thread_queue::thread_queue(int depth, struct queue_ring *ring)
{
        ring->queue_list = new struct message_queue_data[depth];
        for(int i = 0; i < depth; i++) {
                (ring->queue_list + i)->need_join = 0;
        }
};


void FadhilRiyanto::threading::thread_helper::queue_debugger(int depth, struct queue_ring *ring)
{
        log_info("checking need_join_state");
        for(int i = 0; i < depth; i++) {
                log_debug("need_join %d: %s", i, (ring->queue_list + i)->need_join == 1 ? "true" : "false");
        }
};