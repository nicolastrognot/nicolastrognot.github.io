##
## Makefile for strace in /home/papadi_a/work/epitech/Tek2/PSU/PSU_2016_strace
##
## Made by alexis papadimitriou
## Login   <papadi_a@epitech.net>
##
## Started on  Tue Apr 11 12:03:40 2017 alexis papadimitriou
## Last update Sun Apr 16 14:49:19 2017 Nicolas TROGNOT
##

RM		=	rm -f

CC		=	gcc

CFLAGS		+=	-Werror -Wextra -Wall -W -I./include

SRCS		=	srcs/main.c \
			srcs/pid.c \
			srcs/sighandler.c \
			srcs/strace.c \
			srcs/verbose.c \
			srcs/verbose_bis.c \
			srcs/quit.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	strace

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
