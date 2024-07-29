// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "header/command_parser.h"
#include <cstddef>
#include <stdexcept>

namespace FadhilRiyanto {

command_parser::command_parser(std::string rawstr, 
                                struct command_parser_config *parseconf)
{
        this->rawstr = rawstr;
        this->parseconf = parseconf;
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
                throw std::invalid_argument("not a command");
        }
}

std::string command_parser::get_raw_command(void)
{
        auto [has_value, cur_off] = this->command_has_value();

        if (has_value) {
                return this->rawstr.substr(0, cur_off);
        } else {
                return this->rawstr;
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