// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */


#ifndef DAEMON_H
#define DAEMON_H

class daemon {
        public:
        daemon(); /* reserved */

        bool reg_eventloop();
        bool stop(int id);
        bool stop_all();
};

#endif