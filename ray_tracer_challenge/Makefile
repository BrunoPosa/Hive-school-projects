NAME		=	ray_tracer

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

SRCS 		=	functions.c \
				main.c \
				printer.c \
				tests.c \
				create.c \
				tests_colours.c \
				functions_colours.c \
				functions_canvas.c

HEADER = ./inc/ray_tracer.h

MANPATH = $(addprefix ./srcs/, $(SRCS))
						
OBJS		=	$(MANPATH:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lm -g
					
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