#include "../../headers/command_parser.h"
#include "../../headers/ctx.h"
#include <tgbot/tgbot.h>
#include <string>
#include <fmt/core.h>
#include <stdio.h>

/* local */
#include "headers/_reg.h"

int module_main::module_init(TgBot::Bot *bot, TgBot::Message::Ptr msg, 
                                struct ini_config *config, struct ctx *ctx,
                                struct FadhilRiyanto::string_utils::command_parser_result *res)
{
        this->bot = bot;
        this->msg = msg;
        this->config = config;
        this->ctx = ctx;
        
        this->module_next(res->command);
        return 0; /* temp return */
}

int module_main::module_next(std::string input)
{

        printf("module called \"%s\"\n", input.c_str());
        if (!input.compare("/start")) {
                fmt::print("command called\n");
        }

        return 0;
}