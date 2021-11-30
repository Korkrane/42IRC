NAME	=	ircserv

SRCS	=	./srcs/main.cpp \
			./srcs/client_query_parser.cpp \
			./srcs/build_replies.cpp \
			./srcs/build_server.cpp \
			./srcs/client_cmd_parser.cpp \
			./srcs/tmp_utils.cpp \
			./srcs/Commands/Away.cpp \
			./srcs/Commands/Cap.cpp \
			./srcs/Commands/Join.cpp \
			./srcs/Commands/Kick.cpp \
			./srcs/Commands/Kill.cpp \
			./srcs/Commands/List.cpp \
			./srcs/Commands/Mode.cpp \
			./srcs/Commands/Myhelp.cpp \
			./srcs/Commands/Names.cpp \
			./srcs/Commands/Nick.cpp \
			./srcs/Commands/Notice.cpp \
			./srcs/Commands/Oper.cpp \
			./srcs/Commands/Part.cpp \
			./srcs/Commands/Primsg.cpp \
			./srcs/Commands/Quit.cpp \
			./srcs/Commands/Topic.cpp \
			./srcs/Commands/User.cpp \
			./srcs/Commands/Who.cpp

OBJS		=	${SRCS:.cpp=.o}

FLAGS		=	-Wall -Wextra -Werror -std=c++98 #-g3 -fsanitize=address

RM			=	rm -rf

# Verifier s'il faut clang++ ou c++
CC			=	c++

INCLUDES	=	./includes/channel.hpp \
				./includes/client.hpp \
				./includes/colors.hpp \
				./includes/Commands.hpp \
				./includes/exceptions.hpp \
				./includes/Headers.hpp \
				./includes/irc.hpp \
				./includes/replies.hpp \
				./includes/server.hpp

HEAD		=	./includes/

${NAME}	:	${OBJS}
			${CC} -o $@ ${OBJS} ${FLAGS}

#echo "ircserv compiled !"

all:		${NAME}

%.o: %.c
			@${CC} ${CLAGS} -I${HEAD} -c $< -o $@

clean	:
			${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

re		:	clean all

.PHONY:		all clean fclean re
