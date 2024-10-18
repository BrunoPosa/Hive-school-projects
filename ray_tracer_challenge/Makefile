NAME		=	ray_tracer

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

SRCS 		=	functions.c \
				main.c \
				printer.c \
				test.c

HEADER = ./inc/ray_tracer.h

MANPATH = $(addprefix ./srcs/, $(SRCS))
						
OBJS		=	$(MANPATH:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
					
%.o:%.c
			@$(CC) $(CFLAGS) -c $< -o $@		

clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)
					
re:			fclean all

debug:		CFLAGS += -g
debug:		re

.PHONY:			all clean fclean re debug