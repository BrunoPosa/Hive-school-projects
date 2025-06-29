NAME	= PhoneBook
FLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

HEADERS	= Contact.class.hpp \
		  PhoneBook.class.hpp

SRCS	= main.cpp \
		  Contact.cpp \
		  PhoneBook.cpp

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	c++ $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@echo nothing to clean. use fclean

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re