NAME		= At_least_this_beats_coffee-making
EXERCISE	= cpp--05 - ex03
FSANITNAME	= buildFsanitiz
VALGRNAME	= buildValgrind

CXX			= c++
FLAGS		= -std=c++11 -Wall -Wextra -Werror #-O3
DEBUGFLAGS	= -Wpedantic -Wshadow -g -O0 -fsanitize=address -fsanitize=undefined #-v
VALGRFLAGS	= -Wpedantic -Wshadow -g -O0
RM			= rm -rf



HEADERS	=	Bureaucrat.hpp \
			AForm.hpp \
			ShrubberyCreationForm.hpp \
			RobotomyRequestForm.hpp \
			PresidentialPardonForm.hpp \
			Intern.hpp

SRCS	=	main.cpp \
			Bureaucrat.cpp \
			AForm.cpp \
			ShrubberyCreationForm.cpp \
			RobotomyRequestForm.cpp \
			PresidentialPardonForm.cpp \
			Intern.cpp



all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS)

clean:
	$(RM) $(FSANITNAME) $(VALGRNAME)

fclean: clean
	$(RM) $(NAME) a.out *_shrubbery

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