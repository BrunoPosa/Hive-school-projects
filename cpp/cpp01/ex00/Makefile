NAME	= BraiiiiiiinnnzzzZ
FLAGS	= -std=c++11 -Wall -Wextra -Werror
RM		= rm -rf

HEADERS	= Zombie.hpp

SRCS	= 	main.cpp \
			Zombie.cpp \
			newZombie.cpp  \
			randomChump.cpp

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	c++ $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@echo nothing to clean. use fclean

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re