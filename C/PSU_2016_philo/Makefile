##
## Makefile for Makefile in /home/wadel_n/Tek2/PSU_2016_philo
##
## Made by Nicolas Wadel
## Login   <wadel_n@epitech.net>
##
## Started on  Fri Mar 10 09:43:39 2017 Nicolas Wadel
## Last update Sun Mar 19 20:41:46 2017 Nicolas TROGNOT
##

CC	=		gcc -pthread

NAME	=		philo

SRC	=		srcs/main.c \
			srcs/error.c \
			srcs/action.c \
			srcs/algo.c \
			srcs/misc.c

OBJ	=		$(SRC:.c=.o)

CFLAGS	=		-W -Wall -Werror -Wextra -I./inc

RM	=		rm -rf

LIB	=		-Wl,-rpath -Wl,./lib -L./lib -lriceferee

all:			$(NAME)

$(NAME):		$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(LIB)

clean:
			$(RM) $(OBJ)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:			all clean fclean re
