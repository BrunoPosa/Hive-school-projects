# COLOURS 
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
END			=	\033[0m


NAME		=	miniRT

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

SRCS 		=	main.c \
				file_to_list.c \
				file_to_list_scene.c \
				printer.c \
				linked_list.c \
				process_list.c \
				utils.c \
				utils2.c \
				error.c \
				assign_node_type.c \
				process_nodes.c \
				check_count_of_types.c \
				list_legality.c \
				process_3d_xyz.c \
				process_ratio.c \
				process_cd.c \
				process_ch.c \
				process_elements1.c \
				process_elements2.c \
				process_rgb.c \
				process_sd.c \
				process_xyz.c \
				process_utils.c \
				process_fov.c \
				rt_render_scene.c \
				rt_create.c \
				rt_colours.c \
				rt_tuples.c \
				rt_free_rt.c \

# rt_init_camera.c \
# rt_init_mlx.c don't need this if mlx runs in the main()

HEADER = ./inc/file_to_list.h

MLXDIR      = ../MLX42/
MLXLIB      = $(MLXDIR)build/libmlx42.a
MLXFLAGS    = -ldl -lglfw -pthread -L "$$HOME/.brew/opt/glfw/lib/"
MLXHEADERS  = -I $(MLXDIR)include

MANPATH = $(addprefix ./srcs/, $(SRCS))

OBJS		=	$(MANPATH:%.c=%.o)

LIBFT		= ../libft/libft.a

LIBHEADER = ../libft/libft.h

all:			$(NAME)

$(NAME):		$(MLXLIB) $(OBJS) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) -lm $(MLXLIB) $(MLXFLAGS) $(MLXHEADERS) $(LIBFT) -I $(LIBHEADER) -o $(NAME) -g
			@echo "$(GREEN) Files compiled $(END)"

$(MLXLIB):
	cmake $(MLXDIR) -B $(MLXDIR)build && make -C $(MLXDIR)build -j4

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
