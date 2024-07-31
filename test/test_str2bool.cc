// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include <gtest/gtest.h>
#include "header/string_helper.h"

TEST(str2bool, tolower) 
{
        std::string sample = "abCDe";
        std::string ret = FadhilRiyanto::string_utils::string_helper::string_lowercase(sample);

        EXPECT_STREQ(ret.c_str(), "abcde");

}

TEST(str2bool, str2bool) 
{
        std::string sample = "true";
        bool ret = FadhilRiyanto::string_utils::string_helper::str2bool(sample);

        EXPECT_EQ(ret, true);

}

TEST(str2bool, str2bool_false) 
{
        std::string sample = "truewe";
        bool ret = FadhilRiyanto::string_utils::string_helper::str2bool(sample);

        EXPECT_EQ(ret, false);

}


int main()
{
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
}