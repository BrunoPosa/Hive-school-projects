NAME	= PhoneBook
FLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
SRCS	= main.cpp \
		  Contact.cpp

all: $(NAME)

$(NAME):
	c++ $(FLAGS) -o $(NAME) $(SRCS)

clean:
	@echo nothing to clean. use fclean

fclean:
	$(RM) $(NAME)

re: fclean all
