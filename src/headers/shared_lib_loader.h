// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#ifndef SHARED_LIB_LOADER_H
#define SHARED_LIB_LOADER_H

#include "../internal_config.h"

namespace FadhilRiyanto::dlsys {

struct loaded_libs {
        int             n;
        void            *ptr[bot_module_N];
};

class shared_lib_loader {
public:
        static void open_and_append(struct loaded_libs *loaded_libs, char* dlname, int cur_literator);
        static void config_module_load(char** module_list, struct loaded_libs *loaded_libs,
                                                                int n);
        static void close_all_lib(struct loaded_libs *loaded_libs);
};

} /* namespace */

#endif