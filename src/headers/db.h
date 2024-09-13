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
#include <string>

namespace FadhilRiyanto::db {

        

        class key_value {
        private:
                db *dbptr;
        public:
                void bind(db *db);

                /* not implemented yet */
                void set(std::string key, std::string value);
                void get(std::string key);
                
                void dump_all();
                
        };
}

#endif