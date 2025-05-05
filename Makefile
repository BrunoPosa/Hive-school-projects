NAME        = ircserv
FSANITNAME    = $(NAME)Fsan
VALGRNAME    = $(NAME)Val

CXX            = c++
FLAGS        = -std=c++17 -Wall -Wextra -Werror #-O3 #-DNDEBUG
DEBUGFLAGS    = -Wpedantic -Wshadow -g -O0 -fsanitize=address -fsanitize=undefined #-v
VALGRFLAGS    = -Wpedantic -Wshadow -g -O0
RM            = rm -rf


HEADIR		=	inc/
HEADERS    =    $(HEADIR)irc.hpp \
				$(HEADIR)Socket.hpp \
				$(HEADIR)Config.hpp \

<<<<<<< HEAD
SRCDIR		=	src/
SRCS    =   $(SRCDIR)main.cpp \
			$(SRCDIR)Config.cpp \
			$(SRCDIR)Server.cpp \
			$(SRCDIR)Socket.cpp \
			$(SRCDIR)Client.cpp \
			$(SRCDIR)Error.cpp \
			$(SRCDIR)cmd/Nick.cpp \
			$(SRCDIR)cmd/User.cpp \
			$(SRCDIR)cmd/Join.cpp \
			$(SRCDIR)cmd/PrivMsg.cpp \
=======
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
>>>>>>> d44b94b (more cmds done)



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
