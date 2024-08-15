// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <mongoc/mongoc.h>
#include "headers/db.h"

void FadhilRiyanto::db::db::setup_ptr(struct ctx *ctx)
{
        this->ctx = ctx;
}

void FadhilRiyanto::db::db::setup_conn(const char* uri)
{
        mongoc_init();
        this->ctx->client = mongoc_client_new(uri);
}

void FadhilRiyanto::db::db::select(char* dbname, char* collname)
{
        this->ctx->coll = mongoc_client_get_collection(ctx->client, dbname, collname);
}

void FadhilRiyanto::db::db::clean()
{
        mongoc_collection_destroy(this->ctx->coll);
        mongoc_client_destroy(this->ctx->client);
        mongoc_cleanup();
}