#include "../../../headers/modules.h"

class start_command : public register_new_msg_mod {
public:
        std::string command;
        struct ctx *ctx;
        TgBot::Bot *bot;
        TgBot::Message::Ptr *msg;
        TgBot::Api *api;
        struct ini_config *config;

        void req(struct ctx *ctx, TgBot::Bot *bot, TgBot::Message::Ptr *msg, TgBot::Api *api,
                struct ini_config *config);

        void run(void);
};