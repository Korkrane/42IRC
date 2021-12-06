INC_DIR		=	includes
SRC_DIR		=	srcs
HEADER		=	./includes/
NAMES		=	main.cpp \
				Server/Server.cpp \
				Client/Client.cpp \
				Channel/Channel.cpp \
				Utils/tmp_utils.cpp \
				Commands/ServerQueries/Admin.cpp \
				Commands/OptionalFeatures/Away.cpp \
				Commands/OptionalFeatures/Cap.cpp \
				Commands/ServerQueries/Info.cpp \
				Commands/ChannelOperations/Invite.cpp \
				Commands/ChannelOperations/Join.cpp \
				Commands/ChannelOperations/Kick.cpp \
				Commands/Miscellaneous/Kill.cpp \
				Commands/ChannelOperations/List.cpp \
				Commands/ConnectionRegistration/Mode.cpp \
				Commands/Other/Myhelp.cpp \
				Commands/ChannelOperations/Names.cpp \
				Commands/ConnectionRegistration/Nick.cpp \
				Commands/SendingMessages/Notice.cpp \
				Commands/ConnectionRegistration/Oper.cpp \
				Commands/ChannelOperations/Part.cpp \
				Commands/SendingMessages/Privmsg.cpp \
				Commands/ConnectionRegistration/Quit.cpp \
				Commands/ConnectionRegistration/ConnectionRegistration.cpp \
				Commands/ServerQueries/Time.cpp \
				Commands/ChannelOperations/Topic.cpp \
				Commands/Other/Unknown.cpp \
				Commands/ConnectionRegistration/User.cpp \
				Commands/OptionalFeatures/Users.cpp \
				Commands/ServerQueries/Version.cpp \
				Commands/UserBasedQueries/Who.cpp \

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
				./includes/IRCTest.hpp \
				./includes/User.hpp \
				./includes/ErrorHandling.hpp \

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

run:		$(NAME)
			./ircserv 6667 pass

clean:
			@$(RM) $(OBJS)
			@echo "Deleted all but executable"

fclean:		clean
			@$(RM) $(NAME)
			@echo "Everything deleted"

re		:	clean all

.PHONY:		all clean fclean re
