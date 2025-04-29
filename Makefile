NAME        = ircserv
FSANITNAME    = $(NAME)Fsan
VALGRNAME    = $(NAME)Val

CXX            = c++
FLAGS        = -std=c++17 -Wall -Wextra -Werror #-O3 #-DNDEBUG
DEBUGFLAGS    = -Wpedantic -Wshadow -g -O0 -fsanitize=address -fsanitize=undefined #-v
VALGRFLAGS    = -Wpedantic -Wshadow -g -O0
RM            = rm -rf



HEADERS    =    inc/irc.hpp \
				inc/error.hpp \
				inc/Client.hpp \
				inc/Channel.hpp 

SRCS    =    src/main.cpp \
			 src/ArgCheck.cpp \
			 src/Channel.cpp \
			 src/Client.cpp \
			 src/Error.cpp \
			 src/ProcessCmd.cpp \
			 src/Server.cpp \
			 src/cmd/Join.cpp \
			 src/cmd/Kick.cpp \
			 src/cmd/Mode.cpp \
			 src/cmd/Nick.cpp \
			 src/cmd/Ping.cpp \
			 src/cmd/PrivMsg.cpp \
			 src/cmd/Topic.cpp \
			 src/cmd/User.cpp 



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
	git commit -m "$(NAME) - save state"
	git push
	git status




.PHONY: all clean fclean re fs val git
