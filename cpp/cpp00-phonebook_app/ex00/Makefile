NAME	= megaphone
FLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
SRCS	= megaphone.cpp

all: $(NAME)

$(NAME): $(SRCS)
	c++ $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@echo nothing to clean. use fclean

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re