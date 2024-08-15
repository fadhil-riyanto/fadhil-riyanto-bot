// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

/* reserved */

#ifndef CTX_H
#define CTX_H

#include <mongoc/mongoc.h>

struct ctx {
        mongoc_client_t *mongodb_ctx;
        long    reserved;
};

#endif