NAME	= HI_THIS_IS_BRAIN
CXX		= clang++
FLAGS	= -std=c++11 -Wall -Wextra -Werror
RM		= rm -rf

HEADERS	=

SRCS	=	main.cpp

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@echo nothing to clean. use fclean

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re