NAME	= BraiiiiiiinnnzzzZ
FLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

HEADERS	= Zombie.class.hpp

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