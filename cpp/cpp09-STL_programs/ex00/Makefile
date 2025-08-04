NAME		= btc
EXERCISE	= cpp--09 - ex00
DEBUG_NAME	= debugBuild
INPUT_FILE	= ./input.txt

CXX			= c++
FLAGS		= -std=c++17 -Wall -Wextra -Werror
DEBUG_BASE	= -Wpedantic -Wshadow -g -O0 #-v
DEBUG_STL	= -D_GLIBCXX_DEBUG
DEBUG_FSAN	= -fsanitize=address -fsanitize=undefined
RM			= rm -rf



HEADERS	=	BitcoinExchange.hpp

SRCS	=	main.cpp \



all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) $(DEBUG_NAME)

fclean: clean
	$(RM) $(NAME) a.out

re: fclean all



debug: fclean
	@echo "####################### debug STL #######################"
	$(CXX) $(FLAGS) $(DEBUG_BASE) $(DEBUG_STL) -o $(DEBUG_NAME) $(SRCS)
	./$(DEBUG_NAME) $(INPUT_FILE)

fs: fclean
	@echo "####################### fsanitize #######################"
	$(CXX) $(FLAGS) $(DEBUG_BASE) $(DEBUG_FSAN) -o $(DEBUG_NAME) $(SRCS)
	./$(DEBUG_NAME) $(INPUT_FILE)

val: fclean
	@echo "####################### valgrind #######################"
	$(CXX) $(FLAGS) $(DEBUG_BASE) -o $(DEBUG_NAME) $(SRCS)
	valgrind --leak-check=full --show-leak-kinds=all ./$(DEBUG_NAME) $(INPUT_FILE)

git: fclean
	clear
	git status
	git add .
	git status
	git commit -m "$(EXERCISE) save state"
	git push
	git status



.PHONY: all clean fclean re debug fs val git