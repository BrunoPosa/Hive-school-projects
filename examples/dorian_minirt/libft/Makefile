# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 15:27:30 by djagusch          #+#    #+#              #
#    Updated: 2023/07/27 08:19:27 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

CC = cc
CFLAGS = -I$I -std=c99 -O3 -Wall -Wextra -Werror
OS = $(shell uname)

#ifneq ($(OS),Darwin)
CFLAGS += -Wno-unused-result
#endif

NAME = libft.a

S := srcs
O := objs
I := ../incl

HEADER = $I/libft.h

FILES = ft_count_elements \
ft_free_array \
ft_free_int_array \
ft_print_matrix \
ft_free \
ft_printf \
ft_printf_char \
ft_printf_hex \
ft_printf_int \
ft_printf_pointer \
ft_printf_string \
ft_printf_udec \
ft_printf_util \
ft_printf_char_fd \
ft_printf_fd \
ft_printf_hex_fd \
ft_printf_int_fd \
ft_printf_pointer_fd \
ft_printf_string_fd \
ft_printf_udec_fd \
ft_printf_util_fd \
ft_abs \
ft_atof \
ft_atoi \
ft_atol \
ft_atoll \
ft_bits \
ft_lenbase \
ft_max \
ft_min \
ft_pow \
ft_scale \
ft_which_extr \
ft_small_endian \
ft_lstadd_back \
ft_lstadd_front \
ft_lstclear \
ft_lstdelone \
ft_lstiter \
ft_lstlast \
ft_lstmap \
ft_lstnew \
ft_lstprint \
ft_lstsize \
ft_bzero \
ft_calloc \
ft_memchr \
ft_memcmp \
ft_memcpy \
ft_memmove \
ft_memset \
ft_print_array \
ft_putchar \
ft_putchar_fd \
ft_putendl \
ft_putendl_fd \
ft_putnbr \
ft_putnbr_fd \
ft_putstr \
ft_putstr_fd \
get_next_line \
ft_count_words \
ft_dectobase_str \
ft_empty_str \
ft_isalnum \
ft_isalpha \
ft_isascii \
ft_isdigit \
ft_isprint \
ft_isspace \
ft_itoa \
ft_get_word \
ft_split \
ft_split2 \
ft_strchr \
ft_strcmp \
ft_strdup \
ft_striteri \
ft_strjoin \
ft_strlcat \
ft_strlcpy \
ft_strlen \
ft_strmapi \
ft_strncmp \
ft_strnstr \
ft_strrchr \
ft_strtrim \
ft_substr \
ft_tolower \
ft_toupper \
ft_frac \
ft_sign

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name $(FILE).c))

OBJS := $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS := $(dir $(OBJS))

all: $(NAME)

$(NAME): $(OBJS) $(SRCS) $(HEADER)
	@ar rc $(NAME) $(OBJS)

$O/%.o: $S/%.c $(HEADER) | $O
	@$(CC) $(CFLAGS) -c $< -o $@ -g
	@echo "$(COLOUR_GREEN) $@ successfully created$(COLOUR_END)"

$O:
	@mkdir -p $(O_DIRS)

clean:
	@rm -f $(OBJS)
	@if [ -d $O ]; then $(RM) -rf $O $(O_DIRS); fi

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re