#include <gtest/gtest.h>

#include "header/command_parser.h"

TEST(compare_test, test_if_command_is_valid) 
{
        /* parse config */
        struct FadhilRiyanto::command_parser_config parse_config = {
              .command_prefix = '/'
        };

        std::string sample = "/info";
        FadhilRiyanto::command_parser parser(sample, &parse_config);
        
        std::string retstr = parser.get_raw_command();

        EXPECT_STREQ(retstr.c_str(), "/info");
}

TEST(compare_test, test_if_value_is_valid) 
{
        /* parse config */
        struct FadhilRiyanto::command_parser_config parse_config = {
              .command_prefix = '/'
        };

        std::string sample = "/info abc";
        FadhilRiyanto::command_parser parser(sample, &parse_config);
        
        std::string retstr = parser.get_raw_value();

        EXPECT_STREQ(retstr.c_str(), "abc");
}

TEST(compare_test, test_if_value_is_invalid) 
{
        /* parse config */
        struct FadhilRiyanto::command_parser_config parse_config = {
              .command_prefix = '/'
        };

        std::string sample = "/info";
        FadhilRiyanto::command_parser parser(sample, &parse_config);
        
        std::string retstr = parser.get_raw_value();

        EXPECT_EQ(retstr.empty(), true);
}

int main() 
{
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
}