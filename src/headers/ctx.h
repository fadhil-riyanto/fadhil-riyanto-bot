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
#include "command_parser.h"

struct ctx {
        mongoc_client_t *mongodb_ctx;
        struct FadhilRiyanto::string_utils::command_parser_result *parse_result;
        long    reserved;
};

struct memory_struct {
        char                    *memory;
        size_t                  size;
};

#endif