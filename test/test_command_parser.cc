// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <gtest/gtest.h>

#include "header/command_parser.h"

struct FadhilRiyanto::command_parser_config parse_config = {
        .command_prefix = '/',
        .bot_username = "@fadhil_riyanto_bot"
};

TEST(compare_test, test_if_command_is_valid) 
{
        struct FadhilRiyanto::command_parser_result res;
        std::string sample = "/info";

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_command();

        EXPECT_STREQ(retstr.c_str(), "/info");
}

TEST(compare_test, test_if_value_is_valid) 
{
        std::string sample = "/info abc";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_value();

        EXPECT_STREQ(retstr.c_str(), "abc");
}

TEST(compare_test, test_if_value_is_invalid) 
{
        std::string sample = "/info";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_value();

        EXPECT_EQ(retstr.empty(), true);
}

int main() 
{
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
}