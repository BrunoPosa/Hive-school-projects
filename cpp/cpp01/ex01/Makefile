NAME	= Moar_brainz!
CXX		= clang++
FLAGS	= -std=c++17 -Wall -Wextra -Werror
RM		= rm -rf

HEADERS	= Zombie.class.hpp

SRCS	=	main.cpp \
			Zombie.cpp \
			zombieHorde.cpp

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@echo nothing to clean. use fclean

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re