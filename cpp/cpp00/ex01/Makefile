NAME	= PhoneBook
FLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

HEADERS	= Contact.hpp \
		  PhoneBook.hpp

SRCS	= main.cpp \
		  Contact.cpp \
		  PhoneBook.cpp

all: $(NAME)

$(NAME): $(SRCS)
	c++ $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@echo nothing to clean. use fclean

fclean:
	$(RM) $(NAME)

re: fclean all
