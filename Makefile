# ********************************************* #
#                                               #
#                      ::::::|::::||:::|:|:::|  #
#  Makefile            ||::|::|:||::||:|::||||  #
#                      :|:|:|||:||:||||||:::::  #
#                                               #
#                                               #
#  C20230612140008 :|::::                       #
#  U20230612160125 :|||||                       #
#                                               #
# ********************************************* #

ifndef OUTPUT
.SILENT:
endif

NAME	=	computor
ARGS	=	"x"
SRCS	=	Computor_v1.cpp Debug.cpp main.cpp \
			StringTools.cpp
HEAD	=	Makefile Computor_v1.hpp header.hpp \
			Debug.hpp defines.hpp StringTools.hpp
SHELL	=	/bin/sh
CC		=	clang++ -std=c++20 -Wfatal-errors
CCFLAGS	=	-Wall -Werror -Wextra -g -Wfatal-errors
OBJS	=	$(SRCS:.cpp=.o)
VAL		=	valgrind
VALFLAG	=	--tool=memcheck \
			--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--show-reachable=yes
all:		$(NAME)
$(NAME):	$(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)
$(OBJS):	%.o : %.cpp $(HEAD)
	$(CC) $(CCFLAGS) -o $@ -c $<
	echo -n ".";
clean:
	-rm -f $(OBJS)
fclean:		clean
	-rm -f $(NAME)
re:			fclean all
rt:			re t
vf:			all
	$(VAL) $(VALFLAG) ./$(NAME) $(ARGS)
t:			all
	./tests.sh
tt:			all
	./$(NAME) $(ARGS)
v:			all
	$(VAL) ./$(NAME) $(ARGS)

