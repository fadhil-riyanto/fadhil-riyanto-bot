// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

/* reserved */

#ifndef CTX_H
#define CTX_H

#include "db.h"

struct ctx {
        FadhilRiyanto::db::db *mongodb_ctx;
        long    reserved;
};

#endif