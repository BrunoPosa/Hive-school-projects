NAME        = circle

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -rf

MLXDIR      = ../MLX42/
MLXLIB      = $(MLXDIR)build/libmlx42.a
MLXFLAGS    = -ldl -lglfw -pthread -L "$$HOME/.brew/opt/glfw/lib/"
MLXHEADERS  = -I $(MLXDIR)include

LIBFT		= ../libft/libft.a

SRCS        = project_two.c
OBJS        = $(SRCS:.c=.o) \
			  ../ray_tracer_challenge/srcs/functions_tuples.o \
			  ../ray_tracer_challenge/srcs/create.o

all:	$(NAME)

$(NAME): $(MLXLIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lm $(MLXLIB) $(LIBFT) $(MLXFLAGS) $(MLXHEADERS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLXLIB):
	cmake $(MLXDIR) -B $(MLXDIR)build && make -C $(MLXDIR)build -j4

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
