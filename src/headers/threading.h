// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef THREADING_H
#define THREADING_H

#include <tgbot/tgbot.h>

namespace FadhilRiyanto::threading {

struct message_queue_data {
        TgBot::Message::Ptr data;

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
        static void queue_debugger(int depth, struct queue_ring *ring);
};

class thread_queue {
public:
        thread_queue(int depth, struct queue_ring *ring);
        bool send_queue(struct queue_ring *ring, TgBot::Message::Ptr message);
};

}


#endif
