CC = g++
LIB = -lTgBot -lboost_system -lssl -lcrypto -lpthread
DEBUGFLAGS = -ggdb3
OBJDIR = build

inih_parser:
	${CC} src/inih_parser.cc -c -o ${OBJDIR}/inih_parser.o ${DEBUGFLAGS}
	${CC} submodule/inih/ini.c -c -o ${OBJDIR}/ini.o ${DEBUGFLAGS}
	

main_bot: 
	${CC} src/bot.cc -c -o ${OBJDIR}/bot.o ${DEBUGFLAGS}

all_libs: inih_parser main_bot

all: build/*.o
	${CC} $^ -o fadhil_riyanto_bot ${LIB}