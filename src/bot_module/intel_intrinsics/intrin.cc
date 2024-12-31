#include "headers/intrin.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <curl/easy.h>
#include <fmt/format.h>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/cdefs.h>
#include <tgbot/types/ReplyParameters.h>
#include "../../headers/attr.h"
#include "../../headers/ctx.h"
#include "../../headers/string_helper.h"
#include <curl/curl.h>
#include <unistd.h>
#include "../../../submodule/pugixml/src/pugixml.hpp"
#include <fmt/ranges.h>
#include <vector>

/* initialize with preloaded memory */
static void alloc_intel_intrinsics_data(struct intel_intrinsics_data *parsed_data)
{

}

static __hot int start_parse(struct memory_struct *chunk_data, std::string instruction_search, 
        struct intel_intrinsics_data *parsed_data)
{
        pugi::xml_document doc;
        pugi::xml_parse_result ret = doc.load_string(chunk_data->memory);
        if (!ret)
                return -1;

        pugi::xml_node root_node = doc.child("intrinsics_list");

        for(pugi::xml_node intrin_arr = root_node.child("intrinsic"); intrin_arr; intrin_arr = intrin_arr.next_sibling("intrinsic")) {
                if (!instruction_search.compare(intrin_arr.attribute("name").as_string())) {
                        parsed_data->name = strdup(intrin_arr.attribute("name").as_string());
                        parsed_data->return_data->etype = strdup(intrin_arr.child("return").attribute("etype").as_string());
                        parsed_data->return_data->type = strdup(intrin_arr.child("return").attribute("type").as_string());
                        parsed_data->return_data->varname = strdup(intrin_arr.child("return").attribute("varname").as_string());

                        for(pugi::xml_node intrin_param = intrin_arr.child("parameter"); intrin_param; intrin_param = intrin_param.next_sibling("parameter")) {
                                void *ptr = realloc(parsed_data->parameter, sizeof(struct _intel_intrin_parameter) * parsed_data->parameter_len);

                                if (!ptr) {
                                        perror("realloc failed");
                                } else {
                                        parsed_data->parameter = (struct _intel_intrin_parameter*)ptr;
                                        parsed_data->parameter[parsed_data->parameter_len - 1].etype = strdup(intrin_param.attribute("etype").as_string());
                                        parsed_data->parameter[parsed_data->parameter_len - 1].type = strdup(intrin_param.attribute("type").as_string());
                                        parsed_data->parameter[parsed_data->parameter_len - 1].varname = strdup(intrin_param.attribute("varname").as_string());
                                        
                                        parsed_data->parameter_len = parsed_data->parameter_len + 1;
                                }
                        }

                        parsed_data->description = strdup(intrin_arr.child("description").text().get());
                        parsed_data->header = strdup(intrin_arr.child("header").text().get());

                        for(pugi::xml_node cpuid_node = intrin_arr.child("CPUID"); cpuid_node; cpuid_node = cpuid_node.next_sibling("CPUID")) {
                                std::string cpuid_str = std::string(cpuid_node.text().get());
                                // std::cout << cpuid_str << std::endl;
                                parsed_data->cpuid->push_back(cpuid_str);
                        }

                        parsed_data->instruction->form = strdup(intrin_arr.child("instruction").attribute("form").as_string());
                        parsed_data->instruction->name = strdup(intrin_arr.child("instruction").attribute("name").as_string());
                        parsed_data->instruction->xed = strdup(intrin_arr.child("instruction").attribute("xed").as_string());

                        parsed_data->operation = strdup(intrin_arr.child("operation").text().get());

                        parsed_data->category = strdup(intrin_arr.child("category").text().get());
                        
                        // parsed_data->parameter->type = strdup(intrin_arr.child("return").attribute("type").as_string());
                        // parsed_data->parameter->varname = strdup(intrin_arr.child("return").attribute("varname").as_string());
                }
        }
        return 0;
}

static std::string funcparam_generator(struct intel_intrinsics_data *parsed_data)
{
        std::string buf;
        for(int i = 0; i < parsed_data->parameter_len - 1 && parsed_data->parameter_len != 1; i++) {
                if (i + 1 == parsed_data->parameter_len - 1) {
                        buf = buf + parsed_data->parameter[i].type + " " + parsed_data->parameter[i].varname;
                } else {
                        buf = buf + parsed_data->parameter[i].type + " " + parsed_data->parameter[i].varname + ", ";
                }
        }

        return buf;
}

static void intel_xml_intrin_memalloc()
{
        
}

static void intel_xml_intrin_cleanup(struct intel_intrinsics_data *intel_intrin)
{
        free(intel_intrin->name);
        free(intel_intrin->return_data->etype);
        free(intel_intrin->return_data->type);
        free(intel_intrin->return_data->varname);

        if (intel_intrin->parameter_len == 1) {
                free(intel_intrin->parameter);
        } else { 
                for(int i = 0; i < intel_intrin->parameter_len - 1; i++) {
                        free(intel_intrin->parameter[i].etype);
                        free(intel_intrin->parameter[i].type);
                        free(intel_intrin->parameter[i].varname);
                }
                free(intel_intrin->parameter);
        }

        free(intel_intrin->description);
        free(intel_intrin->header);

        free(intel_intrin->instruction->form);
        free(intel_intrin->instruction->xed);
        free(intel_intrin->instruction->name);

        free(intel_intrin->instruction);

        free(intel_intrin->operation);
        free(intel_intrin->category);
        
        delete intel_intrin->cpuid;

        free(intel_intrin);
}

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
        curl_easy_setopt(curl_handle, CURLOPT_URL, "http://0.0.0.0:8080/data-3-6-9.xml.xml");
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

        struct intel_intrinsics_data *intel_intrin = (struct intel_intrinsics_data*)malloc(sizeof(struct intel_intrinsics_data));
        intel_intrin->return_data = (struct _intel_intrin_return*)malloc(sizeof(struct _intel_intrin_return));
        intel_intrin->parameter = (struct _intel_intrin_parameter*)malloc(sizeof(struct _intel_intrin_parameter) * 1);
        intel_intrin->parameter_len = 1;
        intel_intrin->instruction = (struct _intel_instruction*)malloc(sizeof(struct _intel_instruction));
        intel_intrin->cpuid = new std::vector<std::string>({});

        start_parse(&chunk_data, this->ctx->parse_result->value, intel_intrin);


        TgBot::ReplyParameters::Ptr reply_param(new TgBot::ReplyParameters());
        reply_param->chatId = (*this->msg)->chat->id;
        reply_param->messageId = (*this->msg)->messageId;

        std::string formatted = fmt::format("<b>Synopsis</b>\n"
                "<pre >\n{} {}({})</pre>\n"
                "<code>#include &lt;{}&gt;</code>\n"
                "instuction: <code>{} {}</code>\n"
                "CPUID: <code>{}</code>"
                "\n\n"
                "<b>Description</b>\n"
                "{}"
                "\n\n"
                "<b>Operation</b>\n"
                "<code>{}</code>",
                intel_intrin->return_data->type, intel_intrin->name, funcparam_generator(intel_intrin),
                intel_intrin->header, 
                FadhilRiyanto::string_utils::string_helper::string_lowercase(intel_intrin->instruction->name),
                intel_intrin->instruction->form,
                fmt::join(*intel_intrin->cpuid, " + "),
                intel_intrin->description, intel_intrin->operation

        );

        this->bot->getApi().sendMessage(
                (*this->msg)->chat->id, formatted, 
                NULL,
                reply_param, nullptr, "HTML");

        cleanup_all(&chunk_data);
        intel_xml_intrin_cleanup(intel_intrin);
}