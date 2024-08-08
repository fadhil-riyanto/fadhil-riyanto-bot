#include "../../headers/base_module.h"
#include "../../headers/ctx.h"
#include <tgbot/tgbot.h>
#include <string>
#include <fmt/core.h>

namespace FadhilRiyanto::mod {

class module_start : public base_module {
        TgBot::Bot *bot;
        TgBot::Message::Ptr msg;
        struct ini_config *config;
        struct ctx *ctx;

        int module_init(TgBot::Bot *bot, TgBot::Message::Ptr msg, 
                                        struct ini_config *config, struct ctx *ctx)
        {
                this->bot = bot;
                this->msg = msg;
                this->config = config;
                this->ctx = ctx;
                
                return 0; /* temp return */
        }

        int module_next(std::string input)
        {
                if (!input.compare("/start")) {
                        fmt::print("command called");
                }

                return 0;
        }



};

}