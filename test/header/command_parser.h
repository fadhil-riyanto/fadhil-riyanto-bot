// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>

namespace FadhilRiyanto {

struct command_parser_config 
{
        char command_prefix;
};

class command_parser {
private:
        std::string rawstr;
        struct command_parser_config *parseconf;
        
        std::tuple<bool, std::string::size_type> command_has_value(void);

public:
        command_parser(std::string rawstr, struct command_parser_config *parseconf);
        std::string get_raw_command(void);
        std::string get_raw_value(void);
};

} /* namespace */


#endif