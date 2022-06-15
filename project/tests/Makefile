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

SERVER_SOURCE	=	../server/source/options/options.c		\

SERVER_OBJ	=	$(SERVER_SOURCE:.c=.o)

TEST_SOURCE	=	test.c	\

TEST_OBJ	=	$(TEST_SOURCE:.c=.o)

INCLUDE_DIRS	+=	-I ../server/include/

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	$(INCLUDE_DIRS)

LDFLAGS	=	-l criterion --coverage

NAME	=	unit_tests

all: $(NAME)

$(NAME): $(SERVER_OBJ) $(TEST_OBJ)
	@$(CC) -o $(NAME) $(SERVER_SOURCE) $(TEST_SOURCE) $(CFLAGS) $(LDFLAGS)
	@./unit_tests
	@gcovr
	@gcovr --branches

clean:
	@$(DELETE_FILE) $(SERVER_OBJ)
	@$(DELETE_FILE) $(TEST_OBJ)

fclean:	clean
	@$(DELETE_FILE) $(NAME)
	@$(DELETE_FILE) *.gcda
	@$(DELETE_FILE) *.gcno

re:	fclean all

.PHONY: all $(NAME) clean fclean re
