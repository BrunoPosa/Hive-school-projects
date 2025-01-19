NAME	= Unnecessary_violence
CXX		= clang++
FLAGS	= -std=c++11 -Wall -Wextra -Werror
RM		= rm -rf

HEADERS	=	Weapon.class.hpp \
			HumanA.class.hpp \
			HumanB.class.hpp

SRCS	=	main.cpp \
			Weapon.cpp \
			HumanA.cpp \
			HumanB.cpp

all: $(NAME)
#make object files in this makefile, and use the $@ correct shorthands for only recompiling the files newer than the target
$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@echo nothing to clean. use fclean

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re