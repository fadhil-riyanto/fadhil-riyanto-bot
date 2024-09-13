// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */


#ifndef REPO_KEY_VALUE_H
#define REPO_KEY_VALUE_H

#include <mongoc/mongoc.h>
#include "inih_parser.h"
#include <string>

namespace FadhilRiyanto::db 
{

        class db_repo {

        private:
                mongoc_client_t *mongodb_ctx;
                mongoc_collection_t *current_coll_state;
                mongoc_cursor_t *current_cursor;
                struct ini_config *config;
                
                virtual void _select_default_coll() = 0;
        };


        class key_value : db_repo {

        private:
                mongoc_client_t *mongodb_ctx;
                mongoc_collection_t *current_coll_state;
                struct ini_config *config;
                
                void _select_default_coll();
        public:
                key_value(mongoc_client_t *mongodb_ctx, struct ini_config *config);

                /* operations */
                bool get(std::string value);
                bool set(std::string value, std::string key);
                
                ~key_value();
        };
} /* namespace */

#endif