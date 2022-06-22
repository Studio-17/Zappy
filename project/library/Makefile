##
## EPITECH PROJECT, 2022
## B-YEP-410-PAR-4-1-zappy-martin.vanaud
## File description:
## Makefile
##

COPY	=	cp -f
COPY_FILE	=	$(COPY)
COPY_DIR	=	$(COPY) -r

DELETE	=	rm -f
DELETE_FILE	=	$(DELETE)
DELETE_DIR	=	$(DELETE) -r

SRC_MINILIB	=	mini/my_atoi.c		\
				mini/my_itoa.c		\
				mini/my_strtoword.c	\
				mini/free_arr.c		\
				mini/my_arrlen.c	\

SRC_NETLIB	=	net/protocol.c				\
				net/header.c				\
				net/protocol/greeting.c		\
				net/protocol/player.c		\
				net/protocol/map.c			\

MINILIB_OBJ	=	$(SRC_MINILIB:.c=.o)
NETLIB_OBJ	=	$(SRC_NETLIB:.c=.o)

INCLUDE_DIRS	+=	-I include/

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	$(INCLUDE_DIRS)

MINILIB_NAME	=	libmini.a
NETLIB_NAME	=	libnet.a

all: minilib netlib

minilib: $(MINILIB_OBJ)
	@ar rc $(MINILIB_NAME) $(MINILIB_OBJ)

netlib: $(NETLIB_OBJ)
	@ar rc $(NETLIB_NAME) $(NETLIB_OBJ)

clean:
	@$(DELETE_FILE) $(MINILIB_OBJ)
	@$(DELETE_FILE) $(NETLIB_OBJ)

fclean:	clean
	@$(DELETE_FILE) $(MINILIB_NAME)
	@$(DELETE_FILE) $(NETLIB_NAME)

re:	fclean all

.PHONY: all minilib netlib clean fclean re
