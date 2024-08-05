#include "header/command_parser.h"
#include "../src/headers/error.h"
#include <cstdio>

int main()
{
        struct FadhilRiyanto::command_parser_config parse_config = {
                .command_prefix = '/',
                .bot_username = "@fadhil_riyanto_bot"
        };


        std::string sample = "/abc info";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        try {
                std::string retstr = parser.get_raw_command();
        } catch (FadhilRiyanto::error::not_command) {
                printf("input invalid");
        }
}