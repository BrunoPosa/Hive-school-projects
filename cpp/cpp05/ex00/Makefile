NAME		= Mommy_when_I_grow_up_I_want_to_be_a_bureaucrat!
EXERCISE	= cpp--05 - ex00
FSANITNAME	= buildFsanitiz
VALGRNAME	= buildValgrind

CXX			= c++
FLAGS		= -std=c++11 -Wall -Wextra -Werror -O3
DEBUGFLAGS	= -Wpedantic -Wshadow -g -O0 -fsanitize=address -fsanitize=undefined
VALGRFLAGS	= -Wpedantic -Wshadow -g -O0
RM			= rm -rf



HEADERS	=	Bureaucrat.hpp \

SRCS	=	main.cpp \
			Bureaucrat.cpp \



all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) $(FSANITNAME) $(VALGRNAME)

fclean:
	$(RM) $(NAME) $(FSANITNAME) $(VALGRNAME)

re: fclean all




fs: fclean $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) $(DEBUGFLAGS) -o $(FSANITNAME) $(SRCS)
	./$(FSANITNAME)

val: fclean $(SRCS) $(HEADERS)
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




.PHONY: all clean fclean re debug val