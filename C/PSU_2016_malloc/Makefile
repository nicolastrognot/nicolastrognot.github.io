##
## Makefile for make in /home/grella_c/rendu/PSU_2016_malloc
##
## Made by Côme Grellard
## Login   <grella_c@epitech.net>
##
## Started on  Wed Jan 25 17:13:25 2017 Côme Grellard
## Last update Fri Feb 10 09:56:43 2017 Nicolas TROGNOT
##

NAME	=	libmy_malloc.so

SRCS	=	srcs/my_malloc.c \
		srcs/misc.c

OBJS	=	$(SRCS:.c=.o)

CC	=	gcc -Iinc

RM	=	rm -f

CFLAGS	+=	-W -Wall -Wextra -Werror -fPIC -lpthread

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -shared -o $(NAME) $(OBJS)

.c.o:		$(CC) $(CFLAGS) -c $(SRCS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
