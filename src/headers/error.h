// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef ERROR_H
#define ERROR_H

#include <exception>

namespace FadhilRiyanto::error {
        class not_command : std::exception {
        public:
                virtual char const* what();
        };
};

#endif