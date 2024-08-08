CC = g++
LIB = -lTgBot -lboost_system -lssl -lcrypto -lpthread -lfmt
DEBUGFLAGS = -ggdb3
OBJDIR = ../../../build
MOD_DIR = ../../../module_build

_reg:
	${CC} _reg.cc -c -o ${OBJDIR}/mod_main_reg.o ${DEBUGFLAGS} -fPIC

command_start:
	${CC} start.cc -c -o ${OBJDIR}/mod_main_start.o ${DEBUGFLAGS} -fPIC

main: _reg command_start
	${CC} ${OBJDIR}/mod_main_reg.o \
		${OBJDIR}/mod_main_start.o\
	 -shared -o ${MOD_DIR}/libmod_main.so
	
	