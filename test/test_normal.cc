// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <cstdio>
#include <gtest/gtest.h>

#include "header/command_parser.h"

/* parse config */
struct FadhilRiyanto::command_parser_config parse_config = {
        .command_prefix = '/',
        .bot_username = "@fadhil_riyanto_bot"
};

TEST(compare_test, general_gc_command_wo_value) 
{
        std::string sample = "abc info";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_command();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "abc info");
}


int main() 
{
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
}