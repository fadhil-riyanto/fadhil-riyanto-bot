#include "headers/help_cb.h"
#include "../../headers/string_helper.h"
#include "headers/help_mod.h"
#include <string>
#include <tgbot/types/InlineKeyboardMarkup.h>
#include <unordered_map>
#include <vector>

void help_cb::req(struct ctx *ctx, TgBot::Bot *bot, TgBot::CallbackQuery::Ptr *cb, TgBot::Api *api,
                struct ini_config *config)
{
        this->ctx = ctx;
        this->bot = bot;
        this->api = api;
        this->cb = cb;
        this->config = config;
}

static std::unordered_map<std::string, std::string> help_data(
        {
                {
                        "main", "/me: show info yourself"
                },
                {
                        "group", "/pin: used to pin a message\n\n"
                                        "/unpin: unpin is the unpinning a messages. "
                },
                {
                        "anime", "/anilist {name}: get detail info from anilist"
                }
        }
);


void help_cb::run(void)
{
        std::vector<TgBot::InlineKeyboardMarkup::Ptr> keyboard;
        std::string args1 = FadhilRiyanto::string_utils::string_helper::split_n_index(
                (*this->cb)->data, 1);

        if (args1 == "0" || args1 == "back") {
                this->bot->getApi().editMessageText("Help menu", 
                        (*this->cb)->message->chat->id,
                        (*this->cb)->message->messageId, 
                        "", "", nullptr, help_mod::__gen_help_keyboard()
                        
                        
                );
        } else {
                std::string text = help_data.find(args1)->second;
                this->bot->getApi().editMessageText(text, 
                        (*this->cb)->message->chat->id,
                        (*this->cb)->message->messageId, 
                        "", "", nullptr, help_mod::__gen_help_keyboard_back()
                        
                        
                );

                // std::cout <<  << std::endl;
        }



        
}