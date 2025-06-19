NAME		= easyfind
EXERCISE	= cpp--08 - ex00
FSANITNAME	= buildFsanitiz
VALGRNAME	= buildValgrind

CXX			= c++
FLAGS		= -std=c++17 -Wall -Wextra -Werror
DEBUGFLAGS	= -Wpedantic -Wshadow -g -O0 -fsanitize=address -fsanitize=undefined #-v
VALGRFLAGS	= -Wpedantic -Wshadow -g -O0
RM			= rm -rf



HEADERS	=	easyfind.hpp

SRCS	=	main.cpp



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

git: fclean
	clear
	git status
	git add .
	git status
	git commit -m "$(EXERCISE) save state"
	git push
	git status




.PHONY: all clean fclean re fs val git