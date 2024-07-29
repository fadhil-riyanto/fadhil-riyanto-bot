CCFLAGS = -ggdb3 -lgtest
CC = g++

test_parse:
	${CC} command_parser.cc -o build/command_parser.o -c ${CCFLAGS}
	${CC} command_parser.cc test_command_parser.cc -o p ${CCFLAGS}
	
clean:
	rm -rf build
	mkdir build
	rm p