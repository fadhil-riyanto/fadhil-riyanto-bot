// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef _DB_H
#define _DB_H

#include <mongoc/mongoc.h>
#include <bson/bson.h>

namespace FadhilRiyanto::db {

        struct ctx {
                mongoc_client_t *client;
                mongoc_collection_t *coll;
                mongoc_cursor_t *cursor;
                bson_error_t error;
                bson_oid_t oid;
                bson_t *doc;
        };

        class db {
        private:
                struct ctx *ctx;
        public:
                void setup_ptr(struct ctx *ctx);
                /* https://github.com/fadhil-riyanto/mongodb-crud/blob/255fd5b8cbec55027a9c6d0e545fb0f13292e486/include/conn.h#L14 */
                void setup_conn(const char* uri);
                void select(char* dbname, char* collname); /* return ctx */
                void clean();
        };
}

#endif