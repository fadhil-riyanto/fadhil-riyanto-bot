CC = g++
LIB = -lTgBot -lboost_system -lssl -lcrypto -lpthread
DEBUGFLAGS = -ggdb3
OBJDIR = build

inih_parser:
	${CC} src/inih_parser.cc -c -o ${OBJDIR}/inih_parser.o ${DEBUGFLAGS}
	${CC} submodule/inih/ini.c -c -o ${OBJDIR}/ini.o ${DEBUGFLAGS}
	
log_c:
	${CC} submodule/log.c-patched/src/log.cc -c -o ${OBJDIR}/log_c.o ${DEBUGFLAGS} -DLOG_USE_COLOR

utils_command_parser:
	${CC} src/utils/command_parser.cc -c -o ${OBJDIR}/utils_command_parser.o ${DEBUGFLAGS}

utils_string_helper:
	${CC} src/utils/string_helper.cc -c -o ${OBJDIR}/utils_string_helper.o ${DEBUGFLAGS}

main_bot: 
	${CC} src/bot.cc -c -o ${OBJDIR}/bot.o ${DEBUGFLAGS}

all_libs: inih_parser main_bot log_c utils_command_parser utils_string_helper

all: build/*.o
	${CC} $^ -o fadhil_riyanto_bot ${LIB}