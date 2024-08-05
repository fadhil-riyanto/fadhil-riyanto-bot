CCFLAGS = -ggdb3 -lgtest
CC = g++

test_parse:
	${CC} command_parser.cc -o build/command_parser.o -c ${CCFLAGS}
	${CC} command_parser.cc test_command_parser.cc -o p ${CCFLAGS}

test_parse_w_username:
	${CC} command_parser.cc test_command_parser_with_username.cc -o p ${CCFLAGS}

test_parse_value:
	${CC} command_parser.cc test_command_parser_value.cc -o p ${CCFLAGS}

test_str2bool:
	${CC} test_str2bool.cc string_helper.cc -o p ${CCFLAGS}

test_normal:
	${CC} test_normal.cc command_parser.cc -o p ${CCFLAGS}

	
clean:
	rm -rf build
	mkdir build
	rm p