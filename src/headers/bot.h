#include "command_parser.h"
#include <tgbot/tgbot.h>

#include "threading.h"

#ifndef BOT_H
#define BOT_H

#include <csignal>

namespace FadhilRiyanto {

class fadhil_riyanto_bot {
private:
        std::string raw_msg;
        struct command_parser_result *res;

        TgBot::Bot bot;
        struct ini_config *config;
        volatile std::sig_atomic_t *signal_status;

        static struct FadhilRiyanto::threading::queue_ring ring;

public:
        fadhil_riyanto_bot(struct ini_config* config, volatile std::sig_atomic_t *signal_status);
        void bot_eventloop(void);
        void bot_show_basic_config(void);
        void bot_handle_message(TgBot::Message::Ptr *msg,
                struct FadhilRiyanto::threading::queue_ring *ring);
        static void bot_run_cleanup(int sigint);
};


} /* namespace */

#endif