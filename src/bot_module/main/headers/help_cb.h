#include "../../../headers/modules.h"

class help_cb : public register_new_cb_mod {
public:
        std::string command;
        struct ctx *ctx;
        TgBot::Bot *bot;
        TgBot::CallbackQuery::Ptr *cb;
        TgBot::Api *api;
        struct ini_config *config;

        void req(struct ctx *ctx, TgBot::Bot *bot, TgBot::CallbackQuery::Ptr *cb, TgBot::Api *api,
                struct ini_config *config);

        void run(void);
};