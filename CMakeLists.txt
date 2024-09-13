cmake_minimum_required(VERSION 3.10)
project(fadhil_riyanto_bot VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIBFLAGS -lTgBot -lboost_system -lssl -lcrypto -lpthread -lfmt -lcurl -lmongoc-1.0 -lbson-1.0)
set(CUSTOM_LIBFLAGS /usr/include/libmongoc-1.0/)

add_library(threading src/utils/threading.cc)
add_library(exception src/exception/not_command.cc)
add_library(inih_parser src/inih_parser.cc submodule/inih/ini.c)
add_library(log_c submodule/log.c-patched/src/log.cc)
add_library(utils_command_parser src/utils/command_parser.cc)
add_library(utils_string_helper src/utils/string_helper.cc)
add_library(int_helper src/utils/int_helper.cc)
add_library(handler src/handler.cc)
add_library(db src/db.cc)
add_library(repo_key_value src/repositories/key_value.cc)

# module
add_library(module_main src/bot_module/main/start.cc src/bot_module/main/_reg.cc)

add_executable(fadhil_riyanto_bot src/bot.cc)
include_directories(/usr/include/libmongoc-1.0/)
include_directories(/usr/include/libbson-1.0/)

target_link_libraries(fadhil_riyanto_bot threading log_c 
                        threading handler exception  
                        utils_command_parser int_helper inih_parser 
                        utils_string_helper db module_main repo_key_value)

target_link_libraries(fadhil_riyanto_bot ${LIBFLAGS})

