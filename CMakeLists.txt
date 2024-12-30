cmake_minimum_required(VERSION 3.10)
project(fadhil_riyanto_bot VERSION 1.0)
find_package(PkgConfig)

pkg_check_modules(FMT REQUIRED IMPORTED_TARGET fmt)
pkg_check_modules(CURL REQUIRED IMPORTED_TARGET libcurl)
pkg_check_modules(LIBMONGOC REQUIRED IMPORTED_TARGET libmongoc-1.0)
pkg_check_modules(LIBBSON REQUIRED IMPORTED_TARGET libbson-1.0)
pkg_check_modules(LIBOPENSSL REQUIRED IMPORTED_TARGET openssl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIBFLAGS -lTgBot)

#lssl -lcrypto -lpthread -lfmt -lcurl -lmongoc-1.0 -lbson-1.0

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
add_library(modules src/bot_module/main/start.cc 
                        src/bot_module/main/help.cc
                        src/bot_module/main/help_mod.cc
                        src/bot_module/main/help_cb.cc

                        src/bot_module/intel_intrinsics/intrin.cc
)

add_executable(fadhil_riyanto_bot src/bot.cc)

include_directories(${LIBMONGOC_INCLUDE_DIRS})
include_directories(${LIBBSON_INCLUDE_DIRS})

# include_directories(/usr/include/libmongoc-1.0/)
# include_directories(/usr/include/libbson-1.0/)

target_link_libraries(fadhil_riyanto_bot threading log_c 
                        threading handler exception  
                        utils_command_parser int_helper inih_parser 
                        utils_string_helper db modules repo_key_value)

# target_link_libraries(fadhil_riyanto_bot  PkgConfig::PKG_FMT)
target_link_libraries(fadhil_riyanto_bot ${LIBFLAGS} PkgConfig::CURL PkgConfig::LIBMONGOC PkgConfig::FMT)
