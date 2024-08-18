# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/25 11:18:16 by bposa             #+#    #+#              #
#    Updated: 2024/08/15 14:25:40 by bposa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread
DEBUGFLAGS	=	-O1 -g 
SANITFLAG	=	-fsanitize=thread -g

# Source files and dependencies
SRCS	= 	philo.c \
			init.c \
			validation.c \
			utils.c \
			utils_extra.c \
			utils_more.c \
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
	@echo debug made

sanit:	$(SRCS) $(DEPS)
	@$(CC) $(CFLAGS) $(SANITFLAG) -o $(NAME) $(SRCS)
	@echo sanit made

.PHONY:	all clean fclean re debug