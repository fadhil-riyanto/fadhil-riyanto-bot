CC = g++
LIB = -lTgBot -lboost_system -lssl -lcrypto -lpthread -lfmt
DEBUGFLAGS = -ggdb3
OBJDIR = ../../../build

_reg:
	${CC} _reg.cc -c -o ${OBJDIR}/mod_main_reg.o ${DEBUGFLAGS}

command_start:
	${CC} start.cc -c -o ${OBJDIR}/mod_main_start.o ${DEBUGFLAGS}

clean:
	rm ${OBJDIR}/mod_main_reg.o ${OBJDIR}/mod_main_start.o

# /* module makefile */	
module_main: clean _reg command_start