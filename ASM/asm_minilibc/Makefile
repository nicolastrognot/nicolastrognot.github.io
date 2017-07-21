NAME		=	libasm.so

CC		=	ld -shared

OBJS	= $(SRCS:.asm=.o)

%.o: %.asm
	nasm -f elf64 $< -o $@

RM		=	rm -f

SRCS		=	srcs/strlen.asm 	\
			srcs/strcmp.asm 	\
			srcs/strchr.asm 	\
			srcs/memset.asm 	\
			srcs/memcpy.asm 	\
			srcs/strncmp.asm 	\
			srcs/strcasecmp.asm 	\
			srcs/rindex.asm 	\
			srcs/strpbrk.asm 	\
			srcs/strcspn.asm 	\
			srcs/memmove.asm 	\
			srcs/strstr.asm 	\
			bonus/memchr.asm 	\
			bonus/strcat.asm 	\
			bonus/strncat.asm 	\
			bonus/atoi.asm 		\
			bonus/atol.asm

CFLAGS		+=	-W -Wall -Werror -Wextra

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -o $(NAME) $(OBJS)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
