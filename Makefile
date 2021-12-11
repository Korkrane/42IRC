INC_DIR		= includes
SRC_DIR		= srcs

NAMES		= main.cpp Client.cpp Server.cpp
SRCS		= $(addprefix $(SRC_DIR)/, $(NAMES))

OBJS		= $(SRCS:.cpp=.o)

NAME		= ircserv

CC			= clang++
FLAGS		= -Wall -Wextra -Werror -std=c++98 -g

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

re:			fclean all

.PHONY:		all clean fclean re
