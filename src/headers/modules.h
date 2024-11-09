#ifndef MODULES_H
#define MODULES_H

#include <tgbot/tgbot.h>
#include <tgbot/Api.h>
#include <tgbot/types/CallbackQuery.h>
#include "inih_parser.h"

struct property_options {
        int allow_in_groups;

};

class register_new_msg_mod
{
public:
        void req(struct ctx *ctx, TgBot::Bot *bot, TgBot::Message::Ptr *msg, TgBot::Api *api,
                struct ini_config *config);

        void run(void);
// private:
//         struct property_options prop;
//         /* internal data and properties */

//         void set_command_properties();
};

class register_new_cb_mod
{
public:
        void req(struct ctx *ctx, TgBot::Bot *bot, TgBot::CallbackQuery::Ptr *cb, TgBot::Api *api,
                struct ini_config *config);

        void run(void);
// private:
//         struct property_options prop;
//         /* internal data and properties */

//         void set_command_properties();
};

#endif