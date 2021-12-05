INC_DIR		=	includes
SRC_DIR		=	srcs
HEADER		=	./includes/
NAMES		=	main.cpp \
				Server/Server.cpp \
				Client/Client.cpp \
				Channel/Channel.cpp \
				tmp_utils.cpp \
				Commands/Admin.cpp \
				Commands/Away.cpp \
				Commands/Cap.cpp \
				Commands/Info.cpp \
				Commands/Invite.cpp \
				Commands/Join.cpp \
				Commands/Kick.cpp \
				Commands/Kill.cpp \
				Commands/List.cpp \
				Commands/Mode.cpp \
				Commands/Myhelp.cpp \
				Commands/Names.cpp \
				Commands/Nick.cpp \
				Commands/Notice.cpp \
				Commands/Oper.cpp \
				Commands/Part.cpp \
				Commands/Privmsg.cpp \
				Commands/Quit.cpp \
				Commands/Time.cpp \
				Commands/Topic.cpp \
				Commands/Unknown.cpp \
				Commands/User.cpp \
				Commands/Users.cpp \
				Commands/Version.cpp \
				Commands/Who.cpp \

#build_server.cpp 
#build_replies.cpp 

INCLUDES	=	./includes/channel.hpp \
				./includes/Client.hpp \
				./includes/Commands.hpp \
				./includes/exceptions.hpp \
				./includes/irc.hpp \
				./includes/replies.hpp \
				./includes/Server.hpp \
				./includes/Headers.hpp \
				./includes/Colors.hpp \
				./includes/ClientUtils.hpp \
				./includes/IRCTest.hpp 

#./includes/client.hpp
#./includes/server.hpp

SRCS		= $(addprefix $(SRC_DIR)/, $(NAMES))

OBJS		= $(SRCS:.cpp=.o)

NAME		= ircserv

CFLAGS		= -g -DDEBUG -g3 -fsanitize=address#-DDEBUG#-Wall -Wextra -Werror -std=c++98 #-g3 -fsanitize=address

CC			= clang++

FLAGS		= -Wall -Wextra -Werror -std=c++98 #-g

RM			= rm -f

.cpp.o:
			@$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS)
			@echo "Object files compiled"
			@$(CC) $(FLAGS) $(OBJS) -I$(INC_DIR) -o $(NAME)
			@echo "Executable created"
			@echo "Compilation finished"

all:		$(NAME)

clean:
			@$(RM) $(OBJS)
			@echo "Deleted all but executable"

fclean:		clean
			@$(RM) $(NAME)
			@echo "Everything deleted"

re		:	clean all

.PHONY:		all clean fclean re
