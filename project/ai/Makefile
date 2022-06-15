##
## EPITECH PROJECT, 2022
## B-YEP-410-PAR-4-1-zappy-martin.vanaud
## File description:
## Makefile
##

CC	=	gcc

COPY	=	cp -f
COPY_FILE	=	$(COPY)
COPY_DIR	=	$(COPY) -r

DELETE	=	rm -f
DELETE_FILE	=	$(DELETE)
DELETE_DIR	=	$(DELETE) -r

MAIN_SOURCE	=	source/main.c			\

SOURCE	=	source/client/client.c				\
			source/options/options.c			\
			source/options/usage.c				\

MAIN_OBJ	=	$(MAIN_SOURCE:.c=.o)

OBJ	=	$(SOURCE:.c=.o)

INCLUDE_DIRS	+=	-I ../library/include/
INCLUDE_DIRS	+=	-I ..
INCLUDE_DIRS	+=	-I include/
INCLUDE_DIRS	+=	-I include/client/
INCLUDE_DIRS	+=	-I include/options/

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	$(INCLUDE_DIRS)

LDFLAGS	+=	-lm
LDFLAGS	+=	-L ../library/

LDLIBS	+=	-llist
LDLIBS	+=	-lmini
LDLIBS	+=	-lnet

NAME	=	zappy_ai

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(OBJ)
	@make -C ../library/
	@$(CC) -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	@$(DELETE_FILE) $(MAIN_OBJ)
	@$(DELETE_FILE) $(OBJ)

fclean:	clean
	@$(DELETE_FILE) $(NAME)

re:	fclean all

.PHONY: all $(NAME) clean fclean re
