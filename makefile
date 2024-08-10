CC = g++
LIB = -lTgBot -lboost_system -lssl -lcrypto -lpthread -lfmt
DEBUGFLAGS = -ggdb3
OBJDIR = build

exception_list:
	${CC} src/exception/not_command.cc -c -o ${OBJDIR}/exception_not_command.o ${DEBUGFLAGS}

threading:
	${CC} src/utils/threading.cc -c -o ${OBJDIR}/utils_threading.o ${DEBUGFLAGS}

inih_parser:
	${CC} src/inih_parser.cc -c -o ${OBJDIR}/inih_parser.o ${DEBUGFLAGS}
	${CC} submodule/inih/ini.c -c -o ${OBJDIR}/ini.o ${DEBUGFLAGS}
	
log_c:
	${CC} submodule/log.c-patched/src/log.cc -c -o ${OBJDIR}/log_c.o ${DEBUGFLAGS} -DLOG_USE_COLOR

utils_command_parser:
	${CC} src/utils/command_parser.cc -c -o ${OBJDIR}/utils_command_parser.o ${DEBUGFLAGS}

utils_string_helper:
	${CC} src/utils/string_helper.cc -c -o ${OBJDIR}/utils_string_helper.o ${DEBUGFLAGS}

int_helper:
	${CC} src/utils/int_helper.cc -c -o ${OBJDIR}/int_helper.o ${DEBUGFLAGS}

main_bot: 
	${CC} src/bot.cc -c -o ${OBJDIR}/bot.o ${DEBUGFLAGS}

shared_lib_loader: 
	${CC} src/shared_lib_loader.cc -c -o ${OBJDIR}/shared_lib_loader.o ${DEBUGFLAGS}

handler: 
	${CC} src/handler.cc -c -o ${OBJDIR}/handler.o ${DEBUGFLAGS}

# /* module makefile */	
module_main:
	${CC} src/bot_module/main/start.cc -c -o ${OBJDIR}/mod_main_start.o ${DEBUGFLAGS}
	${CC} src/bot_module/main/_reg.cc -c -o ${OBJDIR}/mod_main_reg.o ${DEBUGFLAGS}

all_libs: inih_parser main_bot log_c utils_command_parser utils_string_helper threading int_helper\
		exception_list handler shared_lib_loader module_main

link: build/*.o
	${CC} $^ -o fadhil_riyanto_bot ${LIB}