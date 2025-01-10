# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 11:46:33 by djagusch          #+#    #+#              #
#    Updated: 2023/07/28 11:45:29 by smorphet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc
CFLAGS = -Wall -Werror -Wextra
OS := $(shell uname)

ifeq ($(OS),Darwin)
XFLAGS = -framework OpenGL -framework AppKit
MINILIBX = mlx/libmlx.a
LIBS = -L$(dir $(MINILIBX)) -lmlx -Llibft -lft
else
MINILIBX = mlx_linux/libmlx.a
LIBS = -Llibft -lft -L$(dir $(MINILIBX)) -lmlx_Linux \
	-L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
endif

RM = /bin/rm -f
RMDIR = /bin/rmdir -p

LIBFT = libft/libft.a

S = srcs
O = objs
I = incl
SB = srcs_bonus
OB = objs_bonus
IB = incl_bonus

FILES = camera \
	get_colour \
	box_distance \
	cylinder_distance \
	disk_distance \
	dist_cone \
	get_normal \
	light \
	set_unique \
	min_distance \
	plane_distance \
	sphere_distance \
	triangle_distance \
	cone_distance \
	main \
	render \
	clean_up \
	create_bonus_objs \
	create_objs \
	error_handling \
	ft_split3 \
	getters \
	handlers \
	input \
	is_obj \
	light_visibility \
	texture_setup \
	texture_colour \
	set_image \
	set_scene \
	hit_info \
	hit_shader \
	vec_add \
	vec_addf \
	vec_clamp \
	vec_crossprod \
	vec_dist \
	vec_dotprod \
	vec_inv \
	vec_mag \
	vec_mult \
	vec_neg \
	vec_normalize \
	vec_propadd \
	vec_reflect \
	vec_scale \
	vec_sub \
	vec_add_array \
	colour_vec \
	cone_map \
	cylinder_map \
	planar_map \
	sphere_map \
	triangle_map \
	brick_pattern \
	checkers_pattern \
	ascii_parser \
	create_mesh \
	mesh_utils \
	mesh_processors

HEADER_FILES = vector_math \
	minirt \
	objects \
	linux_keys \
	libft \
	shaders \
	macos_keys \
	errors \
	scene \
	mlx \

HEADER_FILES2 = $(HEADER_FILES) patterns

HEADER := $(addprefix $I/,$(addsuffix .h,$(HEADER_FILES)))
HEADER_B := $(addprefix $(IB)/,$(addsuffix _bonus.h,$(HEADER_FILES2)))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name "$(FILE).c"))
OBJS := $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS := $(dir $(OBJS))

SRCS_B := $(foreach FILE,$(FILES),$(shell find $(SB) -type f -name "$(FILE)_bonus.c"))
OBJS_B := $(patsubst $(SB)/%,$(OB)/%,$(SRCS_B:.c=.o))
O_DIRS_B := $(dir $(OBJS_B))

NAME = miniRT
NAME_BONUS = miniRT_bonus

### RULES ###
all: $(NAME) $(NAME_BONUS)

print:
	@echo $(HEADER_B)

minilib: $(MINILIBX)

libft: $(LIBFT)

$(MINILIBX):
	$(MAKE) -C $(dir $(MINILIBX))
	@echo "$(COLOUR_GREEN) $(MINILIBX) successfully created$(COLOUR_END)"

$(LIBFT):
	@$(MAKE) -C libft
	@echo "$(COLOUR_GREEN) $(LIBFT) successfully created$(COLOUR_END)"

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX) $(HEADER)
	@$(CC) $(CFLAGS) $(XFLAGS) $(OBJS) -I$I $(LIBS) -o $(NAME)
	@echo "$(COLOUR_GREEN) $(NAME) successfully created$(COLOUR_END)"

$O:
	@mkdir -p $@ $(O_DIRS)
	
$O/%.o: $S/%.c $(HEADER) | $O
	@$(CC) $(CFLAGS) -I$I -c $< -o $@
	@echo "$(COLOUR_GREEN) $@ successfully created$(COLOUR_END)"

bonus:  $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_B) $(LIBFT) $(MINILIBX) $(HEADER_B)
	@$(CC) $(CFLAGS) $(XFLAGS) $(OBJS_B) -I$(IB) $(LIBS) -o $(NAME_BONUS)
	@echo "$(COLOUR_GREEN) $(NAME_BONUS) successfully created$(COLOUR_END)"

$(OB):
	@mkdir -p $@ $(O_DIRS_B)

$(OB)/%.o: $(SB)/%.c $(HEADER_B) | $(OB)
	@$(CC) $(CFLAGS) -I$(IB) -c $< -o $@
	@echo "$(COLOUR_GREEN) $@ successfully created$(COLOUR_END)"

clean:
	@$(MAKE) -C $(dir $(MINILIBX)) clean
	@$(MAKE) -C libft clean
	@echo "$(COLOUR_RED) $(MINILIBX) removed$(COLOUR_END)"
	@echo "$(COLOUR_RED) $(LIBFT) removed$(COLOUR_END)"
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_B)
	@if [ -d $O ]; then $(RM) -rf $(O_DIRS) $(OBJS_B) $O $(OB); fi

fclean: clean
	@$(MAKE) -C libft fclean
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(COLOUR_RED) $(NAME) removed$(COLOUR_END)"
	@echo "$(COLOUR_RED) $(NAME_BONUS) removed$(COLOUR_END)"

re: fclean $(NAME) $(NAME_BONUS)

.PHONY: all clean fclean re