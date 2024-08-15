// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <mongoc/mongoc.h>
#include <string>
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

mongoc_collection_t* FadhilRiyanto::db::db::select(std::string dbname, std::string collname)
{
        return mongoc_client_get_collection(ctx->client, dbname.c_str(), collname.c_str());
}

mongoc_client_t* FadhilRiyanto::db::db::export_conn()
{
        return this->ctx->client;
}

void FadhilRiyanto::db::db::clean()
{
        mongoc_collection_destroy(this->ctx->coll);
        mongoc_client_destroy(this->ctx->client);
        mongoc_cleanup();
}

void FadhilRiyanto::db::key_value::bind(FadhilRiyanto::db::db *db)
{
        this->dbptr = db;
}

void FadhilRiyanto::db::key_value::dump_all()
{
        const bson_t *doc;
        mongoc_cursor_t *cursor;
        char *str;

        bson_t *query = bson_new();
        cursor = mongoc_collection_find_with_opts(this->dbptr->select("test-db", "collection"), query, NULL, NULL);

        while(mongoc_cursor_next(cursor, &doc)) {
                str = bson_as_canonical_extended_json(doc, NULL);
                printf ("%s\n", str);
                bson_free(str);
        }

}
