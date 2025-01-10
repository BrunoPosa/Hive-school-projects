NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -O3 -I $(MLX42_DIR)/include -I $(LIBFT_DIR)
RM			= rm -rf

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX42_DIR	= MLX42
MLX42_REPO	= https://github.com/codam-coding-college/MLX42.git
MLX42_LIB	= $(MLX42_DIR)/build/libmlx42.a
MLXFLAGS	= -lglfw -pthread -L "$$HOME/.brew/opt/glfw/lib/"

HEADER		= minirt.h
SRCS_DIR	= srcs/
OBJ			= $(SRCS:.c=.o)
OBJS		= $(addprefix $(SRCS_DIR), $(OBJ))
SRCS		= 	main.c \
				file_to_list.c \
				file_to_list_scene.c \
				linked_list.c \
				process_list.c \
				utils.c \
				error.c \
				assign_node_type.c \
				process_nodes.c \
				check_count_of_types.c \
				list_legality.c \
				process_3d_xyz.c \
				process_alr.c \
				process_lbr.c \
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
				rt_intersections.c \
				rt_normals_diffuse.c \
				rt_utils.c \
				rt_create.c \
				rt_colours.c \
				rt_tuples1.c \
				rt_tuples2.c \
				rt_free_rt.c

GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
END			=	\033[0m

all: $(NAME)

$(NAME): $(MLX42_LIB) $(OBJS) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) $(MLX42_LIB) $(MLXFLAGS) $(LIBFT) -lm -o $(NAME)
			@echo "$(GREEN) Program compiled $(END)"

$(MLX42_LIB): $(MLX42_DIR)
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build && $(MAKE) -C $(MLX42_DIR)/build -j4
	@echo "$(YELLOW) MLX42 built.. $(END)"

$(MLX42_DIR):
	@git clone $(MLX42_REPO)
	@echo "$(YELLOW) MLX42 cloned.. $(END)"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "$(YELLOW) Libft compiled.. $(END)"

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS_DIR) $(HEADER) $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX42_DIR)/build" ]; then \
		make -C $(MLX42_DIR)/build clean; \
	fi
	@echo "$(YELLOW) cleaned $(END)"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@if [ -d "$(MLX42_DIR)/build" ]; then \
		$(RM) $(MLX42_DIR)/build; \
	fi
	@echo "$(GREEN) Fcleaned $(END)"

re: fclean all

.PHONY: all clean fclean re norm
