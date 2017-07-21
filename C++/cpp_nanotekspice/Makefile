CC		= g++

RM		= rm -f

NAME		= nanotekspice

LIBNAME		= libnanotekspice.a

SRC_BIN		= Main.cpp

SRCS_LIB	= srcs/Controller.cpp \
		  srcs/Parser.cpp \
		  srcs/LogicGates.cpp \
		  srcs/components/Components.cpp \
		  srcs/components/Input.cpp \
		  srcs/components/Clock.cpp \
		  srcs/components/True.cpp \
		  srcs/components/False.cpp \
		  srcs/components/Output.cpp \
		  srcs/components/C4001.cpp \
		  srcs/components/C4069.cpp \
		  srcs/components/C4071.cpp \
		  srcs/components/C4030.cpp \
		  srcs/components/C4011.cpp \
		  srcs/components/C4013.cpp \
		  srcs/components/C4008.cpp \
		  srcs/components/C4514.cpp \
		  srcs/components/C4040.cpp \
		  srcs/components/C4017.cpp \
		  srcs/components/C4081.cpp

OBJS		= $(SRCS_LIB:.cpp=.o)

OBJ		= $(SRC_BIN:.cpp=.o)

CXXFLAGS	+= -W -Wall -Wextra -Werror -std=c++11

all	: 	$(LIBNAME) $(NAME)

$(NAME)	:	$(OBJ)
	  	$(CC) $(OBJ) $(LIBNAME) $(CPPFLAGS) -o $(NAME) -I./inc

$(LIBNAME) :	$(OBJS)
	  	ar rc $(LIBNAME) $(OBJS)

clean	:
		$(RM) $(OBJS) $(OBJ)
		$(RM) $(LIBNAME)

fclean	:	clean
	 	$(RM) $(NAME)

re	: 	fclean all

.PHONY	: 	all clean fclean re
