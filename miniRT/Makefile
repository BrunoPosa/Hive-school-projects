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
				printer.c \
				linked_list.c \
				file_to_list.c \
				process_list.c \
				utils.c \
				init.c \
				error.c \
				assign_node_type.c \
				process_nodes.c \
				check_count_of_types.c \
				list_legality.c \
				process_3d_xyz.c \
				process_alr.c \
				process_cd.c \
				process_ch.c \
				process_lbr.c \
				process_rgb.c \
				process_sd.c \
				process_xyz.c \
				process_utils.c \
				process_fov.c

HEADER = ./inc/file_to_list.h

MANPATH = $(addprefix ./srcs/, $(SRCS))

OBJS		=	$(MANPATH:%.c=%.o)

LIBFT		= ../libft/libft.a

LIBHEADER = ../libft/libft.h

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJS) -lm -o $(NAME) $(LIBFT) -I $(LIBHEADER) -g
			@echo "$(GREEN) Files compiled $(END)"

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
