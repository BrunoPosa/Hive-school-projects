NAME	:= miniRT
BONUS_NAME := miniRT_bonus

#Compiler options#
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g #-fsanitize=address -g

LIBMLX	:= ./lib/MLX42
SRCDIR  := ./src
PARSE_DIR = $(SRCDIR)/parse
BONUS_SRCDIR := ./bonus
BONUS_PARSE_DIR = $(BONUS_SRCDIR)/parse

#Libft#
LIBFT_DIR	:= ./lib/Libft/
LIBFT		:= $(LIBFT_DIR)/libft.a

HEADERS	:= -I ./inc -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
SRCS	:= $(SRCDIR)/definitions.c \
			$(SRCDIR)/color_utils.c \
			$(SRCDIR)/color_utils_two.c \
			$(SRCDIR)/cylinder.c \
			$(PARSE_DIR)/filehandler.c \
			$(PARSE_DIR)/parsing.c \
			$(PARSE_DIR)/parse_extra.c \
			$(PARSE_DIR)/parsing_utils.c \
			$(PARSE_DIR)/objects_parser.c \
			$(SRCDIR)/error_functions.c \
			$(SRCDIR)/tuple_operations_one.c \
			$(SRCDIR)/tuple_operations_two.c \
			$(SRCDIR)/rays.c $(SRCDIR)/sphere.c \
			$(SRCDIR)/intersections.c \
			$(SRCDIR)/matrix_operations.c \
			$(SRCDIR)/matrix_inverse.c \
			$(SRCDIR)/matrix_transform.c \
			$(SRCDIR)/matrix_transformations_utils.c \
			$(SRCDIR)/normal.c \
			$(SRCDIR)/matrix_utils.c \
			$(SRCDIR)/reflection.c \
			$(SRCDIR)/world.c \
			$(SRCDIR)/main.c \
			$(SRCDIR)/plane.c \
			$(SRCDIR)/color_operations.c \
			$(SRCDIR)/create_structs.c \
			$(SRCDIR)/clean_structs.c \
			$(SRCDIR)/clean_structs_two.c \
			$(SRCDIR)/light.c \
			$(SRCDIR)/view_transform.c \
			$(SRCDIR)/camera.c \
			$(SRCDIR)/shadows.c \
			$(SRCDIR)/pattern.c \
			$(SRCDIR)/cones.c \
			$(SRCDIR)/start_mlx.c \
			$(SRCDIR)/hook.c \
			$(SRCDIR)/bump.c

BONUS_SRCS := $(BONUS_SRCDIR)/bump_bonus.c \
              $(BONUS_SRCDIR)/camera_bonus.c \
              $(BONUS_SRCDIR)/clean_structs_bonus.c \
              $(BONUS_SRCDIR)/clean_structs_two_bonus.c \
              $(BONUS_SRCDIR)/color_operations_bonus.c \
              $(BONUS_SRCDIR)/color_utils_bonus.c \
              $(BONUS_SRCDIR)/color_utils_two_bonus.c \
              $(BONUS_SRCDIR)/cones_bonus.c \
              $(BONUS_SRCDIR)/create_structs_bonus.c \
              $(BONUS_SRCDIR)/cylinder_bonus.c \
              $(BONUS_SRCDIR)/definitions_bonus.c \
              $(BONUS_SRCDIR)/error_functions_bonus.c \
              $(BONUS_SRCDIR)/hook_bonus.c \
              $(BONUS_SRCDIR)/intersections_bonus.c \
              $(BONUS_SRCDIR)/light_bonus.c \
              $(BONUS_SRCDIR)/main_bonus.c \
              $(BONUS_SRCDIR)/matrix_inverse_bonus.c \
              $(BONUS_SRCDIR)/matrix_operations_bonus.c \
			  $(BONUS_SRCDIR)/matrix_transform_bonus.c \
			  $(BONUS_SRCDIR)/matrix_transformations_utils_bonus.c \
			  $(BONUS_SRCDIR)/matrix_utils_bonus.c \
			  $(BONUS_SRCDIR)/normal_bonus.c \
			  $(BONUS_SRCDIR)/plane_bonus.c \
			  $(BONUS_SRCDIR)/rays_bonus.c \
			  $(BONUS_SRCDIR)/reflection_bonus.c \
			  $(BONUS_SRCDIR)/shadows_bonus.c \
			  $(BONUS_SRCDIR)/sphere_bonus.c \
			  $(BONUS_SRCDIR)/start_mlx_bonus.c \
			  $(BONUS_SRCDIR)/tuple_operations_one_bonus.c \
			  $(BONUS_SRCDIR)/tuple_operations_two_bonus.c \
			  $(BONUS_SRCDIR)/view_transform_bonus.c \
			  $(BONUS_SRCDIR)/world_bonus.c \
			  $(BONUS_SRCDIR)/pattern_bonus.c \
			  $(BONUS_PARSE_DIR)/filehandler_bonus.c \
			  $(BONUS_PARSE_DIR)/parsing_bonus.c \
			  $(BONUS_PARSE_DIR)/parse_extra_bonus.c \
			  $(BONUS_PARSE_DIR)/objects_parser_bonus.c \
			  $(BONUS_PARSE_DIR)/parsing_utils_bonus.c

OBJS	:= ${SRCS:.c=.o}
BONUS_OBJS := ${BONUS_SRCS:.c=.o}

all: libmlx $(LIBFT) $(NAME)
bonus: libmlx $(LIBFT) $(BONUS_NAME)

libmlx : .libmlx
.libmlx:
	touch .libmlx
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(PARSE_DIR)/%.o: $(PARSE_DIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(BONUS_SRCDIR)/%.o: $(BONUS_SRCDIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(LIBS) $(HEADERS) -o $(BONUS_NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT) :
	@make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS) $(BONUS_OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf .libmlx
	rm -rf $(LIBFT)
	@rm -rf $(NAME) $(BONUS_NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, bonus
