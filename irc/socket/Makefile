NAME		= socketTest
FSANITNAME	= $(NAME)Fsan
VALGRNAME	= $(NAME)Valg

CXX			= c++
FLAGS		= -std=c++20 -Wall -Wextra -Werror -pthread #-O3 #-DNDEBUG
DEBUGFLAGS	= -Wpedantic -Wshadow -g -O0 -fsanitize=address -fsanitize=undefined #-v
VALGRFLAGS	= -Wpedantic -Wshadow -g -O0
RM			= rm -rf



HEADERS	=	Socket.hpp

SRCS	=	main.cpp \
			Socket.cpp



all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) $(FSANITNAME) $(VALGRNAME)

fclean: clean
	$(RM) $(NAME) a.out

re: fclean all




fs: fclean
	echo ########################################################
	$(CXX) $(FLAGS) $(DEBUGFLAGS) -o $(FSANITNAME) $(SRCS)
	./$(FSANITNAME)

val: fclean
	echo ########################################################
	$(CXX) $(FLAGS) $(VALGRFLAGS) -o $(VALGRNAME) $(SRCS)
	valgrind --leak-check=full --show-leak-kinds=all ./$(VALGRNAME)



.PHONY: all clean fclean re fs val git