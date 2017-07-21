##
## Makefile for Makefile in /home/nicolas.trognot/rendu/PSU_2016_nmobjdump
##
## Made by Nicolas TROGNOT
## Login   <nicolas.trognot@epitech.net>
##
## Started on  Mon Feb 20 10:11:27 2017 Nicolas TROGNOT
## Last update Sun Feb 26 00:32:15 2017 Nicolas TROGNOT
##

CC			=	gcc

RM			=	rm -rf

NM_NAME			=	my_nm

OBJDUMP_NAME		=	my_objdump

NM_SRCS			=	nm/srcs/nm.c \
				nm/srcs/file_handler.c \
				nm/srcs/elf_handler.c \
				nm/srcs/symbol_handler.c \
				nm/srcs/misc.c \
				nm/srcs/types/get_umin.c \
				nm/srcs/types/get_wminwmaj.c \
				nm/srcs/types/get_vminvmaj.c \
				nm/srcs/types/get_umaj.c \
				nm/srcs/types/get_amaj.c \
				nm/srcs/types/get_cmaj.c \
				nm/srcs/types/get_bmaj.c \
				nm/srcs/types/get_rmaj.c \
				nm/srcs/types/get_dmaj.c \
				nm/srcs/types/get_tmaj.c \
				nm/srcs/types/get_dmaj_bis.c

OBJDUMP_SRCS		=	objdump/srcs/objdump.c \
				objdump/srcs/file_handler.c \
				objdump/srcs/elf_handler.c \
				objdump/srcs/misc.c \
				objdump/srcs/flags/set_flags.c \
				objdump/srcs/flags/get_flags.c \
				objdump/srcs/ascii_section.c \
				objdump/srcs/ascii_header.c

NM_OBJS			=	$(NM_SRCS:.c=.o)

OBJDUMP_OBJS		=	$(OBJDUMP_SRCS:.c=.o)

CFLAGS			+=	-W -Wall -Werror -Wextra

all			:	nm objdump

nm			:	CFLAGS += -I./nm/inc/
nm			:	$(NM_NAME)

objdump			:	CFLAGS += -I./objdump/inc/
objdump			:	$(OBJDUMP_NAME)

$(NM_NAME)		:	$(NM_OBJS)
				$(CC) $(NM_OBJS) -o $(NM_NAME)

$(OBJDUMP_NAME)		:	$(OBJDUMP_OBJS)
				$(CC) $(OBJDUMP_OBJS) -o $(OBJDUMP_NAME)

clean			:
				$(RM) $(NM_OBJS) $(OBJDUMP_OBJS)

fclean			:	clean
				$(RM) $(NM_NAME) $(OBJDUMP_NAME)

re			:	fclean all

.PHONY			:	all clean fclean re
