NAME		=	file_to_list

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

SRCS 		=	main.c \
				printer.c 

HEADER = ./inc/file_to_list.h

MANPATH = $(addprefix ./srcs/, $(SRCS))

OBJS		=	$(MANPATH:%.c=%.o)

LIBFT		= ../libft/libft.a

LIBHEADER = ../libft/libft.h

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) -lm -o $(NAME) $(LIBFT) -I $(LIBHEADER)

$(LIBFT):
			@make -C ../libft && make -C ../libft make clean

# %.o:%.c
# 			@$(CC) $(CFLAGS) -c $< -o $@		


clean:
			$(RM) $(OBJS)
			@make -C ../libft clean

fclean:			clean
			$(RM) $(NAME)

re:			fclean all

debug:		CFLAGS += -g
debug:		re

.PHONY:		all clean fclean re debug
