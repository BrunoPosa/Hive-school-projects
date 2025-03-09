NAME		= Mommy_when_I_grow_up_I_want_to_be_a_bureaucrat!
FSANITNAME	= buildFsanitiz
VALGRNAME	= buildValgrind

CXX			= c++
FLAGS		= -std=c++11 -Wall -Wextra -Werror -O3
DEBUGFLAGS	= -Wpedantic -Wshadow -g -O0 -fsanitize=address -fsanitize=undefined
VALGRFLAGS	= -Wpedantic -Wshadow -g -O0
RM			= rm -rf



HEADERS	=	Bureaucrat.hpp \
			Colors.hpp

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

fsanit: fclean $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) $(DEBUGFLAGS) -o $(FSANITNAME) $(SRCS)

val: fclean $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) $(VALGRFLAGS) -o $(VALGRNAME) $(SRCS)

.PHONY: all clean fclean re debug val