NAME		=	ray_tracer

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

# before submission, change the path to the mlx library to be in a system folder or fetch it from the internet
MLXDIR		=	../MLX42/
MLXLIB		=	$(MLXDIR)build/libmlx42.a
MLXFLAGS	=	-ldl -lglfw -pthread -L "$$HOME/.brew/opt/glfw/lib/"
MLXHEADERS	=	-I $(MLXDIR)include

SRCS 		=	main.c \
				printer.c \
				create.c \
				functions_tuples.c \
				functions_colours.c \
				functions_canvas.c \
				functions_utils.c \
				tests.c \
				tests_colours.c \
				project_one.c

HEADER = ./inc/ray_tracer.h

MANPATH = $(addprefix ./srcs/, $(SRCS))

OBJS		=	$(MANPATH:%.c=%.o)

all:			$(NAME)

#$(NAME):		$(MLXLIB) $(OBJS)
#			$(CC) $(CFLAGS) $(OBJS) -lm $(MLXLIB) $(MLXFLAGS) $(MLXHEADERS) -o $(NAME)
$(NAME):		$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -lm -o $(NAME)

%.o:%.c
			@$(CC) $(CFLAGS) -c $< -o $@		

$(MLXLIB):
			cmake $(MLXDIR) -B $(MLXDIR)build && make -C $(MLXDIR)build -j4

clean:
			$(RM) $(OBJS)
#			cd $(MLXDIR)build && make clean

fclean:			clean
			$(RM) $(NAME)
#			$(RM) $(MLXLIB)

re:			fclean all

debug:		CFLAGS += -g
debug:		re

.PHONY:		all clean fclean re debug
