#include "headers/intrin.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <curl/easy.h>
#include <sys/cdefs.h>
#include <tgbot/types/ReplyParameters.h>
#include "../../headers/attr.h"
#include "../../headers/ctx.h"
#include <curl/curl.h>
#include <unistd.h>

static size_t intel_xml_write_callback(void *contents, size_t size, size_t n, void *userp)
{
        size_t realsize = size * n;
        struct memory_struct *mem = (struct memory_struct*)userp;

        char* bytes = (char*)realloc(mem->memory, mem->size + realsize + 1);
        if (!bytes) {
                fprintf(stdout, "error writing, intrin curl can't realloc");
                return 0;
        }

        mem->memory = bytes;
        memcpy(&(mem->memory[mem->size]), contents, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;

        return realsize;

}

static void __hot peform_xml_fetch(struct memory_struct *chunk_data)
{
        CURL *curl_handle;
        CURLcode ret_code;

        

        chunk_data->memory = (char*)malloc(1);
        chunk_data->size = 0;

        curl_handle = curl_easy_init();
        curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.intel.com/content/dam/develop/public/us/en/include/intrinsics-guide/data-3-6-9.xml");
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, intel_xml_write_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)chunk_data);

        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        ret_code = curl_easy_perform(curl_handle);

        if(ret_code != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(ret_code));
        } else {
                printf("%lu bytes retrieved\n", (unsigned long)chunk_data->size);

        }

        curl_easy_cleanup(curl_handle);
        // xml_data_ctx->data = chunk_data;
}

static inline __COLD void cleanup_all(struct memory_struct *chunk_data)
{
        
        free(chunk_data->memory);
}

void intrin_command::req(struct ctx *ctx, TgBot::Bot *bot, TgBot::Message::Ptr *msg, TgBot::Api *api,
                struct ini_config *config) 
{
        this->ctx = ctx;
        this->bot = bot;
        this->api = api;
        this->msg = msg;
        this->config = config;
}

void intrin_command::run()
{
        struct memory_struct chunk_data;
        peform_xml_fetch(&chunk_data);


        TgBot::ReplyParameters::Ptr reply_param(new TgBot::ReplyParameters());
        reply_param->chatId = (*this->msg)->chat->id;
        reply_param->messageId = (*this->msg)->messageId;

        this->bot->getApi().sendMessage(
                (*this->msg)->chat->id, "intel intrinsics", 
                NULL,
                reply_param);

        cleanup_all(&chunk_data);
}