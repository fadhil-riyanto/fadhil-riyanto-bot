// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "header/command_parser.h"
#include <cstdio>
#include <stdexcept>
#include <string>

/* external text include */
#include "../src/headers/error.h"

namespace FadhilRiyanto {

command_parser::command_parser(std::string rawstr, 
                                struct command_parser_config *parseconf, struct command_parser_result *res)
{
        this->rawstr = rawstr;
        this->parseconf = parseconf;
        this->res = res;

        /* init data */
        this->res->my_turn = false;
}

/* return */
std::tuple<bool, std::string::size_type> command_parser::command_has_value(void)
{
        std::string::size_type pos_off;

        if (this->rawstr[0] == this->parseconf->command_prefix) {

                pos_off = this->rawstr.find(" ");
                if (pos_off == std::string::npos) {
                        return {false, 0};
                } else {
                        return {true, pos_off};
                }
        } else {
                throw FadhilRiyanto::error::not_command();
        }
}

std::string command_parser::get_raw_command(void)
{
        auto [has_value, cur_off] = this->command_has_value();
        std::string strret;
        std::string::size_type npos;

        if (has_value) {
                strret = this->rawstr.substr(0, cur_off);
        } else {
                strret = this->rawstr;
        }

        /* find @ */
        npos = strret.find("@");
        
        if (npos == std::string::npos) {
                /* returned on no username detected */
                res->my_turn = true;
                return strret;
        } else {
                /* returned on username */

                if (!this->parseconf->bot_username.compare(strret.substr(npos, cur_off)) 
                        && cur_off != std::string::npos) {

                        res->my_turn = true;
                        return strret.substr(0, npos);
                } else {
                        if (!has_value) {
                                
                                if (!this->parseconf->bot_username.compare(strret.substr(npos, this->rawstr.length() - 1))) {
                                        res->my_turn = true;
                                        return strret.substr(0, npos);
                                }
                        }
                        return "invalid";
                }
                
        }
}

std::string command_parser::get_raw_value(void) 
{
        auto [has_value, cur_off] = this->command_has_value();

        if (has_value) {
                /* 
                * cur + 1 = trim space char
                */
                return this->rawstr.substr((cur_off + 1), this->rawstr.length());
        } else {
                return "";
        }
}

}