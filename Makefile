# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread
DEBUGFLAGS	=	-O0 -g

# Source files and dependencies
SRCS	= 	philo.c \
			validation.c 

DEPS	=	philo.h

# Executable name
NAME	=	philo

# Rules
all:	$(NAME)

$(NAME):	$(SRCS) $(DEPS)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS)
	@echo build made

clean:
	@echo cleaned
# @rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

debug: 

.PHONY:	all clean fclean re debug