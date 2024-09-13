// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "../headers/key_value.h"
#include <bson/bson.h>
#include <cstddef>

FadhilRiyanto::db::key_value::key_value(mongoc_client_t *mongodb_ctx, 
                                        struct ini_config *config)
{
        this->mongodb_ctx = mongodb_ctx;
        this->config = config;

        this->_select_default_coll();
}

void FadhilRiyanto::db::key_value::_select_default_coll()
{
        this->current_coll_state = mongoc_client_get_collection(
                this->mongodb_ctx,
                config->mongodb_db_target,
                "key_value_store" 
        );
}

bool FadhilRiyanto::db::key_value::set(std::string value, std::string key)
{
        bson_t *document;
        bson_error_t error;
        bson_oid_t oid;

        bool ret;

        document = bson_new ();
        bson_oid_init (&oid, NULL);
        BSON_APPEND_OID (document, "_id", &oid);
        BSON_APPEND_UTF8 (document, "hello", "world");


        ret = mongoc_collection_insert(this->current_coll_state, MONGOC_INSERT_NONE, document, NULL, &error);

        if (!ret) {
                fprintf(stderr, "%s\n", error.message);
        }

        bson_destroy(document);
        return ret;
}

FadhilRiyanto::db::key_value::~key_value()
{
        mongoc_collection_destroy(this->current_coll_state);

}