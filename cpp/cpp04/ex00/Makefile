NAME	= Polymorphism
CXX		= c++
FLAGS	= -std=c++11 -Wall -Wextra -Werror -Wshadow
RM		= rm -rf

HEADERS	=	Animal.hpp \
			Dog.hpp \
			Cat.hpp \
			# WrongCat.hpp

SRCS	=	main.cpp \
			Animal.cpp \
			Dog.cpp \
			Cat.cpp \
			# WrongCat.cpp

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@echo nothing to clean, use fclean

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re