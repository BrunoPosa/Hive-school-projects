# COLOURS 
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
END			=	\033[0m


NAME		=	file_to_list

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

SRCS 		=	main.c \
				printer.c \
				linked_list.c \
				file_to_list.c \
				process_list.c \
				utils.c

HEADER = ./inc/file_to_list.h

MANPATH = $(addprefix ./srcs/, $(SRCS))

OBJS		=	$(MANPATH:%.c=%.o)

LIBFT		= ../libft/libft.a

LIBHEADER = ../libft/libft.h

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) -lm -o $(NAME) $(LIBFT) -I $(LIBHEADER) -g
			@echo "$(GREEN) Files compiled $(END)"

$(LIBFT):
			@make -C ../libft && make -C ../libft make clean

# %.o:%.c
# 			@$(CC) $(CFLAGS) -c $< -o $@		

clean:
			@$(RM) $(OBJS)
			@echo "$(YELLOW)Objects removed$(END)"

fclean:			clean
			@$(RM) $(NAME)

re:			fclean all

debug:		CFLAGS += -g
debug:		re

.PHONY:		all clean fclean re debug
