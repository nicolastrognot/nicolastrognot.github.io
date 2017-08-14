##
## Makefile for lemipc in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_lemipc
##
## Made by alexis papadimitriou
## Login   <papadi_a@epitech.net>
##
## Started on  Tue Mar 28 11:42:52 2017 alexis papadimitriou
## Last update Sun Apr  2 13:24:29 2017 Nicolas TROGNOT
##

RM		=	rm -f

CC		=	gcc

CFLAGS		+=	-Werror -Wextra -Wall -W -I./include

SRCS		=	srcs/main.c \
			srcs/init/client.c \
			srcs/init/client_in.c \
			srcs/init/map.c \
			srcs/core/manhattan.c \
			srcs/core/loop.c \
			srcs/core/check.c \
			srcs/core/client_turn.c \
			srcs/utils/errors.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	lemipc

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
