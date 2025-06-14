NAME		=	ircserv
FSAN_NAME	=	$(NAME)Fsan
VALGR_NAME	=	$(NAME)Valgr

CXX			=	c++
MAIN_FLAGS	=	-std=c++17 -Wall -Wextra -Werror -O3 -DNDEBUG
DEBUG_FLAGS	=	-std=c++17 -Wall -Wextra -Werror -g -O0 -Wpedantic -Wshadow
FSAN_FLAGS	=	-fsanitize=address -fsanitize=undefined


DEFAULT_ARG	=	6667 4242
RM			=	rm -rf
INCDIR		=	inc/
HEADERS		=	$(INCDIR)Server.hpp \
				$(INCDIR)error.hpp \
				$(INCDIR)Client.hpp \
				$(INCDIR)Channel.hpp \
				$(INCDIR)Socket.hpp \
				$(INCDIR)Config.hpp \

SRCDIR	=	src/
SRCS	=	$(SRCDIR)main.cpp \
			$(SRCDIR)Config.cpp \
			$(SRCDIR)Socket.cpp \
			$(SRCDIR)Channel.cpp \
			$(SRCDIR)Client.cpp \
			$(SRCDIR)dispatchCmd.cpp \
			$(SRCDIR)Server.cpp \
			$(SRCDIR)cmd/Join.cpp \
			$(SRCDIR)cmd/Kick.cpp \
			$(SRCDIR)cmd/Mode.cpp \
			$(SRCDIR)cmd/Nick.cpp \
			$(SRCDIR)cmd/Ping.cpp \
			$(SRCDIR)cmd/PrivMsg.cpp \
			$(SRCDIR)cmd/Topic.cpp \
			$(SRCDIR)cmd/User.cpp \
			$(SRCDIR)cmd/Invite.cpp \
			$(SRCDIR)cmd/Part.cpp

OBJDIR	=	obj/
OBJCS	=	$(SRCS:$(SRCDIR)%.cpp=$(OBJDIR)%.o)




all: $(NAME)

$(NAME): $(OBJCS)
	$(CXX) $(MAIN_FLAGS) -o $(NAME) $(OBJCS)

$(OBJDIR)%.o: $(SRCDIR)%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(MAIN_FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR) $(FSAN_NAME) $(VALGR_NAME)

fclean: clean
	$(RM) $(NAME) a.out log.log

re: fclean all




fs: fclean
	echo ########################################################
	$(CXX) $(DEBUG_FLAGS) $(FSAN_FLAGS) -o $(FSAN_NAME) $(SRCS)
	./$(FSAN_NAME) $(DEFAULT_ARG)

val: fclean
	echo ########################################################
	$(CXX) $(DEBUG_FLAGS) -o $(VALGR_NAME) $(SRCS)
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all ./$(VALGR_NAME) $(DEFAULT_ARG)

git: fclean
	clear
	git status
	git add .
	git status
	git commit -m "$(NAME) - save state"
	git push
	git status




.PHONY: all clean fclean re fs val git

