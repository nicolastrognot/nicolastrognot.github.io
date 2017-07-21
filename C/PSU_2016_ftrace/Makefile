##
## Makefile for ftrace in /home/papadi_a/rendu/PSU_2016_ftrace
## 
## Made by Alexis Papadimitriou
## Login   <papadi_a@epitech.net>
## 
## Started on  Sun May  7 22:40:16 2017 Alexis Papadimitriou
## Last update Sun May  7 22:42:02 2017 Alexis Papadimitriou
##

CC		=	gcc

CFLAGS		+=	-Werror -Wextra -Wall -W -I./include

RM		=	rm -rf

NAME		=	ftrace

SRCS		=	srcs/func_handler.c \
			srcs/ftrace_struct_handler.c \
			srcs/call_handler.c \
			srcs/ftrace.c \
			srcs/func_stack.c \
			srcs/main.c

OBJS		=	$(SRCS:.c=.o)

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -lelf -o $(NAME) $(OBJS)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all fclean fclean re
