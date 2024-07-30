#include "command_parser.h"
#include <tgbot/tgbot.h>

#ifndef BOT_H
#define BOT_H

namespace FadhilRiyanto {

class fadhil_riyanto_bot {
private:
        std::string raw_msg;
        struct command_parser_result *res;

        TgBot::Bot bot;

public:
        fadhil_riyanto_bot(const std::string bot_token);
        void bot_eventloop(void);
        void bot_show_basic_config(void);
        void bot_handle_message(void);
};


} /* namespace */

#endif