NAME	= Serena_my_love!
CXX		= c++
FLAGS	= -std=c++11 -Wall -Wextra -Werror
RM		= rm -rf

HEADERS	=	ClapTrap.hpp \
			ScavTrap.hpp

SRCS	=	main.cpp \
			ClapTrap.cpp \
			ScavTrap.cpp

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@echo nothing to clean, use fclean

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re