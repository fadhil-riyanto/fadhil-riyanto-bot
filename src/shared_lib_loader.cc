// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Copyright (C) 2024  Fadhil Riyanto
 * 
 *  https://github.com/fadhil-riyanto/telegram-bot
 */

#include "headers/shared_lib_loader.h"
#include <dlfcn.h>

void FadhilRiyanto::dlsys::shared_lib_loader::open_and_append(struct loaded_libs *loaded_libs, char* dlname,
                                                int cur_literator)
{
        // for(int i = 0; i < loaded_libs->n; i++) {
                (loaded_libs->ptr[cur_literator]) = dlopen(dlname, RTLD_LAZY);
        // }
}


void FadhilRiyanto::dlsys::shared_lib_loader::close_all_lib(struct loaded_libs *loaded_libs)
{
        for(int i = 0; i < loaded_libs->n; i++) {
                dlclose(loaded_libs->ptr[i]);
        }
}

void FadhilRiyanto::dlsys::shared_lib_loader::config_module_load(char** module_list, struct loaded_libs *loaded_libs,
                                                                int n)
{
        loaded_libs->n = n;

        for(int i = 0; i < loaded_libs->n; i++)
        {
                FadhilRiyanto::dlsys::shared_lib_loader::open_and_append(
                        loaded_libs, module_list[i], i
                );
        }
}