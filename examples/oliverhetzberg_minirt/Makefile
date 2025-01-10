NAME := miniRT
CC := cc
CFLAGS := -Wall -Wextra -Werror
LIBMLX := ./MLX42

HEADERS := -I ./headers -I $(LIBMLX)/include -I libft/headers

LIBS_LINUX := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm ./libft/libft.a
LIBS_MAC := $(LIBMLX)/build/libmlx42.a -Iinclude -lglfw \
            -L"/opt/homebrew/Cellar/glfw/3.3.9/lib/" -framework Cocoa \
            -framework OpenGL -framework IOKit ./libft/libft.a

COMMON_SRC := src/main.c \
				src/errors/errors.c	src/errors/freeing.c  src/parsing/check_args.c \
				src/parsing/files.c src/parsing/init.c src/parsing/init1.c src/parsing/parse_mandatory.c \
				src/parsing/parse_objects.c src/parsing/parse_utils.c src/parsing/parse_utils1.c src/parsing/rtfile.c \
				src/ray/ray.c \
				src/utils/utils.c src/utils/utils1.c \
				src/vector/vector.c src/vector/vector1.c src/vector/vector2.c \
				src/figures/color.c src/figures/cylinder.c src/figures/plane.c src/figures/pixel_color.c \
				src/figures/shadow.c src/figures/sphere.c src/figures/utils_figures.c 

VPATH := $(sort $(dir $(COMMON_SRC)))

COMMON_OBJS := $(patsubst %.c, obj/%.o, $(notdir $(COMMON_SRC)))

all: libmlx libft $(NAME)

mac: CFLAGS += -D__MACOS__
mac: libmlx libft $(NAME)_mac

clone_mlx42:
	if [ ! -d "$(LIBMLX)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

libmlx: clone_mlx42
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	make -C ./libft

$(NAME): $(COMMON_OBJS)
	$(CC) $(COMMON_OBJS) $(LIBS_LINUX) -o $(NAME)

$(NAME)_mac: $(COMMON_OBJS)
	$(CC) $(COMMON_OBJS) $(LIBS_MAC) -o $(NAME)

obj/%.o: %.c Makefile
	@mkdir -p obj
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf obj/*.o
	@rm -rf $(LIBMLX)/build
	make -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft clone_mlx42 mac
