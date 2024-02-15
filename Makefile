ifndef OUTPUT
.SILENT:
endif

NAME	=	computor
ARGS	=	"-1 0 -1"
SRCS	=	Computor_v1.cpp main.cpp \
			StringTools.cpp Computor_v1_algo.cpp \
			MathTools.cpp Computor_v1_treats.cpp
HEAD	=	Computor_v1.hpp header.hpp \
			defines.hpp StringTools.hpp MathTools.hpp
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
t1:			all
	./tests.sh
t2:			all
	./permutations.py
t:			t1 t2
tt:			all
	echo "./$(NAME) $(ARGS)"
	./$(NAME) $(ARGS)
v:			all
	$(VAL) ./$(NAME) $(ARGS)
d:			all
	gdb --arg ./$(NAME) $(ARGS)
