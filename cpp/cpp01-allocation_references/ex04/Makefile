NAME	= Sed_is_for_losers
CXX		= clang++
FLAGS	= -std=c++11 -g -Wall -Wextra -Werror
RM		= rm -rf

HEADERS	= Replace.hpp

SRCS	=	main.cpp \
			Replace.cpp

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) text.replace
	$(RM) LoremToHello.log
	$(RM) forbiddenLocation.log

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re