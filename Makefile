INC_DIR		=	includes
SRC_DIR		=	srcs
HEADER		=	./includes/
NAMES		=	main.cpp \
				Channel/Channel.cpp \
				Client/Client.cpp \
				Commands/ChannelOperations/Invite.cpp \
				Commands/ChannelOperations/Join.cpp \
				Commands/ChannelOperations/Kick.cpp \
				Commands/ChannelOperations/List.cpp \
				Commands/ChannelOperations/Mode.cpp \
				Commands/ChannelOperations/Names.cpp \
				Commands/ChannelOperations/Topic.cpp \
				Commands/ConnectionRegistration/Cap.cpp \
				Commands/ConnectionRegistration/ConnectionRegistration.cpp \
				Commands/ConnectionRegistration/Nick.cpp \
				Commands/ConnectionRegistration/Oper.cpp \
				Commands/ConnectionRegistration/User.cpp \
				Commands/SendingMessages/Notice.cpp \
				Commands/SendingMessages/Privmsg.cpp \
				Commands/ServerQueries/Motd.cpp \
				Commands/ServerQueries/Time.cpp \
				Commands/Other/Unknown.cpp \
				Commands/OptionalFeatures/Users.cpp \
				Commands/ServerQueries/Version.cpp \
				Commands/Ping.cpp \
				Commands/Commands.cpp \
				IRCServer/IRCServer.cpp \
				Replies/build_replies.cpp \
				Server/Server.cpp \
				User/User.cpp \
				Utils/ft_split.cpp \
				Utils/tmp_utils.cpp \
				Utils/error_handler.cpp \


INCLUDES	=	./includes/Channel.hpp \
				./includes/Client.hpp \
				./includes/Commands.hpp \
				./includes/IRC.hpp \
				./includes/Replies.hpp \
				./includes/Server.hpp \
				./includes/Colors.hpp \
				./includes/ClientUtils.hpp \
				./includes/IRCServer.hpp \
				./includes/User.hpp \

TEST_SRCS	=	./test/cmd_tests/admin.cpp \
				./test/cmd_tests/away.cpp \
				./test/cmd_tests/time.cpp \
				./test/cmd_tests/unknown.cpp \
				./test/cmd_tests/users.cpp \
				./test/cmd_tests/version.cpp \
				./test/main_test.cpp \

SRCS		= $(addprefix $(SRC_DIR)/, $(NAMES))

OBJS		= $(SRCS:.cpp=.o)

NAME		= ircserv

CC			= clang++

FLAGS		= -DDEBUG -Wall -Wextra -Werror -std=c++98 -g

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
