NAME		= Mommy_when_I_grow_up_I_want_to_be_a_bureaucrat!
DEBUGNAME	= buildDebug
VALGRNAME	= buildValgrind

CXX			= c++
FLAGS		= -std=c++11 -Wall -Wextra -Werror #-O3
DEBUGFLAGS	= -Wpedantic -Wshadow -g -O0 -fsanitize=address -fsanitize=undefined
VALGRFLAGS	= -Wpedantic -Wshadow -g -O0
RM			= rm -rf



HEADERS	=	Bureaucrat.hpp \
			Colors.hpp

COLORS	=	Colors.cpp

SRCS	=	main.cpp \
			Bureaucrat.cpp \



all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) -o $(NAME) $(SRCS) $(COLORS)

clean:
	@echo nothing to clean, use fclean

fclean:
	$(RM) $(NAME) $(DEBUGNAME) $(VALGRNAME)

re: fclean all

debug: fclean $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) $(DEBUGFLAGS) -o $(DEBUGNAME) $(SRCS) $(COLORS)

val: fclean $(SRCS) $(HEADERS)
	$(CXX) $(FLAGS) $(VALGRFLAGS) -o $(VALGRNAME) $(SRCS) $(COLORS)

.PHONY: all clean fclean re debug val