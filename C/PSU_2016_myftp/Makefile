##
## Makefile for Makefile in /home/nicolas.trognot/rendu/Reseau/PSU_2016_myftp
##
## Made by Nicolas TROGNOT
## Login   <nicolas.trognot@epitech.net>
##
## Started on  Wed May 17 11:14:26 2017 Nicolas TROGNOT
## Last update Wed May 17 11:16:06 2017 Nicolas TROGNOT
##

NAME	=	server

SRCS	=	srcs/main.c \
		srcs/misc.c \
		srcs/struct_handler.c \
		srcs/client_handler.c \
		srcs/command_handler.c \
		srcs/commands/login.c \
		srcs/commands/misc.c \
		srcs/commands/file.c \
		srcs/commands/logout.c \
		srcs/commands/type.c \
		srcs/commands/file_transfer.c \
		srcs/commands/transfer.c \
		srcs/commands/dir.c

OBJS	=	$(SRCS:.c=.o)

RM	=	rm -f

CC	=	gcc

CFLAGS	+=	-Wall -Werror -Wextra -I./inc/

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS)

clean	:
		$(RM) $(OBJS)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
