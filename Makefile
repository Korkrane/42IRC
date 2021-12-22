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
				Commands/ChannelOperations/Part.cpp \
				Commands/ChannelOperations/Mode.cpp \
				Commands/ChannelOperations/User_mode.cpp \
				Commands/ChannelOperations/Channel_mode.cpp \
				Commands/ChannelOperations/Names.cpp \
				Commands/ChannelOperations/Topic.cpp \
				Commands/ChannelOperations/Who.cpp \
				Commands/ConnectionRegistration/Cap.cpp \
				Commands/ConnectionRegistration/ConnectionRegistration.cpp \
				Commands/ConnectionRegistration/Nick.cpp \
				Commands/ConnectionRegistration/Oper.cpp \
				Commands/ConnectionRegistration/User.cpp \
				Commands/ConnectionRegistration/Pass.cpp \
				Commands/ConnectionRegistration/Quit.cpp \
				Commands/SendingMessages/Notice.cpp \
				Commands/SendingMessages/Privmsg.cpp \
				Commands/ServerQueries/Motd.cpp \
				Commands/ServerQueries/Time.cpp \
				Commands/ServerQueries/Kill.cpp \
				Commands/Other/Unknown.cpp \
				Commands/OptionalFeatures/Away.cpp \
				Commands/OptionalFeatures/Die.cpp \
				Commands/ServerQueries/Version.cpp \
				Commands/ServerQueries/Ping.cpp \
				Commands/Commands.cpp \
				IRCServer/IRCServer.cpp \
				Replies/build_replies.cpp \
				Server/Server.cpp \
				User/User.cpp \
				Utils/ft_split.cpp \


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
				./includes/ft.hpp \

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

FLAGS		= -D DEBUG=1 -D MALATINI=1 -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address

EXTRA_MA 	= -D MALATINI=1

RM			= rm -f

.cpp.o:
			@$(CC) ${FLAGS} ${EXTRA_MA} -I$(INC_DIR) -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS)
			@echo "Object files compiled"
			@$(CC) $(FLAGS) ${EXTRA_MA} $(OBJS) -I$(INC_DIR) -o $(NAME)
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
