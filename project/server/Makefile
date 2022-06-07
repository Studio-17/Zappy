##
## EPITECH PROJECT, 2022
## B-EPI-000-PAR-0-0-projectname-user.email
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

SOURCE	=	\

MAIN_OBJ	=	$(MAIN_SOURCE:.c=.o)

OBJ	=	$(SOURCE:.cpp=.o)

INCLUDE_DIRS	=	-I source/errors/

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	$(INCLUDE_DIRS)

NAME	=	zappy_server

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(OBJ)
	@$(CC) -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CFLAGS)

clean:
	@$(DELETE_FILE) $(MAIN_OBJ)
	@$(DELETE_FILE) $(OBJ)

fclean:	clean
	@$(DELETE_FILE) $(NAME)

re:	fclean all

.PHONY: all $(NAME) clean fclean re
