##
## Makefile for lemipc in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_lemipc
##
## Made by alexis papadimitriou
## Login   <papadi_a@epitech.net>
##
## Started on  Tue Mar 28 11:42:52 2017 alexis papadimitriou
## Last update Sun Apr  2 21:00:57 2017 alexis papadimitriou
##

RM		=	rm -f

CC		=	gcc

CFLAGS		+=	-Werror -Wextra -Wall -W -I../include/

SRCS		=	srcs/gui.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	lemipc_gui

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -lSDL $(OBJS) -o $(NAME)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
