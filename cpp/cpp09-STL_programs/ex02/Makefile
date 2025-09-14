NAME		= PmergeMe
EXERCISE	= cpp--09 - ex02
DEBUG_NAME	= debugBuild
# PROG_ARGS = `shuf -i 1-21 -n 11; shuf -i 1-21 -n 10` 		# duplicates
PROG_ARGS	= `shuf -i 0-9 -n 9 | tr "\n" " "`
CXX			= c++
FLAGS		= -std=c++20 -Wall -Wextra -Werror
OFLAGS		= -O3 -march=native -mtune=native
DEBUG_BASE	= -Wpedantic -Wshadow -g -O0
DEBUG_STL	= -D_GLIBCXX_DEBUG
DEBUG_FSAN	= -fsanitize=address -fsanitize=undefined
RM			= rm -rf

DEPS	=	PmergeMe.hpp \
			PmergeMe.tpp
SRCS	=	main.cpp \
			PmergeMe.cpp



all: $(NAME)
	./$(NAME) $(PROG_ARGS)

$(NAME): $(SRCS) $(HEADERS) $(DEPS)
	$(CXX) $(FLAGS) $(OFLAGS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(DEBUG_NAME)

fclean: clean
	$(RM) $(NAME) a.out

re: fclean all


trace:
	$(CXX) $(FLAGS) $(OFLAGS) -DCOMPARISON_COUNT -DTRACE $(SRCS) -o $(NAME)
	./$(NAME) $(PROG_ARGS)

debug: fclean
	@echo "####################### debug STL #######################"
	$(CXX) $(FLAGS) $(DEBUG_BASE) $(DEBUG_STL) -o $(DEBUG_NAME) $(SRCS)
	./$(DEBUG_NAME) $(PROG_ARGS)

fs: fclean
	@echo "####################### fsanitize #######################"
	$(CXX) $(FLAGS) $(DEBUG_BASE) $(DEBUG_FSAN) -o $(DEBUG_NAME) $(SRCS)
	./$(DEBUG_NAME) $(PROG_ARGS)

val: fclean
	@echo "####################### valgrind #######################"
	$(CXX) $(FLAGS) $(DEBUG_BASE) -o $(DEBUG_NAME) $(SRCS)
	valgrind --leak-check=full --show-leak-kinds=all ./$(DEBUG_NAME) $(PROG_ARGS)

git: fclean
	clear
	git status
	git add .
	git status
	git commit -m "$(EXERCISE) save state"
	git push
	git status


.PHONY: all clean fclean re debug fs val git