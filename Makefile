# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/25 11:18:16 by bposa             #+#    #+#              #
#    Updated: 2024/07/25 11:18:20 by bposa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread
DEBUGFLAGS	=	-fsanitize=thread -O0 -g

# Source files and dependencies
SRCS	= 	philo.c \
			validation.c \
			utils.c \
			init.c \
			exit.c

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

debug:	$(SRCS) $(DEPS)
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(SRCS)
	@echo debug build made

.PHONY:	all clean fclean re debug