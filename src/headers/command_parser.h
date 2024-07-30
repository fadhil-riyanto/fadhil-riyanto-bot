// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>

namespace FadhilRiyanto::string_utils {

struct command_parser_config 
{
        char command_prefix;
        std::string bot_username;
};

struct command_parser_result 
{
        bool my_turn;
        std::string command;
        std::string value;
};

class command_parser {
private:
        std::string rawstr;
        struct command_parser_config *parseconf;
        struct command_parser_result *res;
        
        std::tuple<bool, std::string::size_type> command_has_value(void);

public:
        command_parser(std::string rawstr, struct command_parser_config *parseconf, struct command_parser_result *res);
        std::string get_raw_command(void);
        std::string get_raw_value(void);
};

} /* namespace */


#endif