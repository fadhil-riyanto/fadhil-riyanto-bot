#include "../../../headers/modules.h"

class intrin_command : public register_new_msg_mod {
public:
        std::string command; /* maybe unused */
        struct ctx *ctx;
        TgBot::Bot *bot;
        TgBot::Message::Ptr *msg;
        TgBot::Api *api;
        struct ini_config *config;

        void req(struct ctx *ctx, TgBot::Bot *bot, TgBot::Message::Ptr *msg, TgBot::Api *api,
                struct ini_config *config);

        void run(void);
};