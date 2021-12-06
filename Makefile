NAME	=	ircserv

SRCS	=	./srcs/main.cpp \
			./srcs/Server/Server.cpp \
			./srcs/Client/Client.cpp \
			./srcs/Channel/Channel.cpp \
			./srcs/tmp_utils.cpp \
			./srcs/build_server.cpp \
			./srcs/build_replies.cpp \
			./srcs/Commands/Admin.cpp \
			./srcs/Commands/Away.cpp \
			./srcs/Commands/Cap.cpp \
			./srcs/Commands/Info.cpp \
			./srcs/Commands/Invite.cpp \
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
			./srcs/Commands/Privmsg.cpp \
			./srcs/Commands/Quit.cpp \
			./srcs/Commands/Time.cpp \
			./srcs/Commands/Topic.cpp \
			./srcs/Commands/Unknown.cpp \
			./srcs/Commands/User.cpp \
			./srcs/Commands/Users.cpp \
			./srcs/Commands/Version.cpp \
			./srcs/Commands/Who.cpp \
			./srcs/Commands/Whois.cpp \
			./srcs/Commands/Whowas.cpp \
			./srcs/Commands/Motd.cpp

OBJS		=	${SRCS:.cpp=.o}

CFLAGS		=	-g -DDEBUG #-fsanitize=address#-DDEBUG#-Wall -Wextra -Werror -std=c++98 #-g3 -fsanitize=address

RM			=	rm -rf

CC			=	clang++

INCLUDES	=	./includes/channel.hpp \
				./includes/client.hpp \
				./includes/colors.hpp \
				./includes/Commands.hpp \
				./includes/exceptions.hpp \
				./includes/irc.hpp \
				./includes/replies.hpp \
				./includes/server.hpp \
				./includes/Headers.hpp

HEADER		=	./includes/

${NAME}	:	${OBJS}
			${CC} -o $@ ${OBJS} ${CFLAGS}

all:		${NAME}

%.o: %.cpp
			${CC} ${CFLAGS} -I${HEADER} -c $< -o $@

clean	:
			${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

re		:	clean all

.PHONY:		all clean fclean re
