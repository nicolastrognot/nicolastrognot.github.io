################################################################################
#                                                                              #
#                       Makefile from the future                               #
#                       For EPITECH TEK2                                       #
#                       Made by: Come GRELLARD & Nicolas TROGNOT               #
#                                                                              #
################################################################################


NAME 		= 	trainmanager

ML 		=	functor.ml	\
			tmdates.ml	\
			helper.ml	\
			link.ml		\
			train.ml	\
			trip.ml		\
			main.ml

MLI 		=	tmdates.mli	\
			helper.mli	\
			link.mli	\
			train.mli	\
			trip.mli

CAMLFLAGS 	= 	-w Aelz -warn-error A str.cma unix.cma

OCAMLC 		= 	ocamlc $(CAMLFLAGS)

RM 		= 	rm -f

all		: 	$(NAME)

$(NAME)		:
			$(OCAMLC) $(MLI) $(ML) -o $(NAME)

clean		:
	 		$(RM) *.cm* *.o .depend *~

fclean		: 	clean
			$(RM) $(NAME)

re		: 	fclean all

.PHONY		: 	all clean fclean re
