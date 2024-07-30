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
        std::string sample = "/info";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_command();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "/info");
}

TEST(compare_test, general_gc_command_w_value) 
{
        std::string sample = "/info abc";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_command();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "/info");
}

TEST(compare_test, mybot_gc_command_wo_value) 
{
        std::string sample = "/info@fadhil_riyanto_bot";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_command();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "/info");
}


TEST(compare_test, mybot_gc_command_w_value) 
{
        std::string sample = "/info@fadhil_riyanto_bot abc de";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_command();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "/info");
}

TEST(compare_test, otherbot_gc_command_wo_value) 
{
        std::string sample = "/info@otherbot";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_command();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "invalid");
}

TEST(compare_test, otherbot_gc_command_w_value) 
{
        std::string sample = "/info@otherbot abde fg";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_command();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "invalid");
}

int main() 
{
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
}