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
        struct FadhilRiyanto::command_parser_result res;

        std::string sample = "/info";
        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        /* get_raw_command must be executed */
        parser.get_raw_command();
        std::string retstr = parser.get_raw_value();
        // printf("%s\n", retstr.c_str());
        // EXPECT_STREQ(retstr.c_str(), "");
        EXPECT_EQ(res.my_turn, true);
}

TEST(compare_test, general_gc_command_w_value_1s) 
{
        struct FadhilRiyanto::command_parser_result res;


        std::string sample = "/info abcde";
        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_value();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "abcde");
}

TEST(compare_test, general_gc_command_w_value_2s) 
{
        std::string sample = "/info abcde dfhi";
        struct FadhilRiyanto::command_parser_result res;


        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_value();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "abcde dfhi");
}

TEST(compare_test, mybot_gc_command_wo_value) 
{
        std::string sample = "/info@fadhil_riyanto_bot";
        struct FadhilRiyanto::command_parser_result res;


        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_value();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "");
}

TEST(compare_test, mybot_gc_command_w_value_1s) 
{
        std::string sample = "/info@fadhil_riyanto_bot abcde";
        struct FadhilRiyanto::command_parser_result res;


        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_value();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "abcde");
}


TEST(compare_test, mybot_gc_command_w_value_2s) 
{
        std::string sample = "/info@fadhil_riyanto_bot abcde dfgisihhe";
        struct FadhilRiyanto::command_parser_result res;


        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_value();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "abcde dfgisihhe");
}


TEST(compare_test, otherbot_gc_command_wo) 
{
        std::string sample = "/info@otherbot";
        struct FadhilRiyanto::command_parser_result res;

        FadhilRiyanto::command_parser parser(sample, &parse_config, &res);
        
        std::string retstr = parser.get_raw_value();
        // printf("%s\n", retstr.c_str());
        EXPECT_STREQ(retstr.c_str(), "");
}

int main() 
{
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
}