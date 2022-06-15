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

SOURCE	=	source/server/communication/request/request.c	\
			source/server/communication/response/response.c	\
			source/server/server.c							\
			source/server/connection/connect/client.c		\
			source/server/connection/connect/server.c		\
			source/server/connection/setup/setup.c			\
			source/errors/errors.c							\
			source/options/options.c						\
			source/options/usage.c							\
			source/zappy/map/map.c							\
			source/zappy/map/resources.c					\

TEST_SOURCE	=	../tests/test.c

MAIN_OBJ	=	$(MAIN_SOURCE:.c=.o)

OBJ	=	$(SOURCE:.c=.o)

TEST_OBJ	=	$(TEST_SOURCE:.c=.o)

INCLUDE_DIRS	+=	-I ../library/include/
INCLUDE_DIRS	+=	-I include/
INCLUDE_DIRS	+=	-I include/server/
INCLUDE_DIRS	+=	-I include/server/communication/
INCLUDE_DIRS	+=	-I include/server/communication/request/
INCLUDE_DIRS	+=	-I include/server/communication/response/
INCLUDE_DIRS	+=	-I include/server/client/
INCLUDE_DIRS	+=	-I include/errors/
INCLUDE_DIRS	+=	-I include/options/
INCLUDE_DIRS	+=	-I include/zappy/
INCLUDE_DIRS	+=	-I include/zappy/elevation/
INCLUDE_DIRS	+=	-I include/zappy/vision/
INCLUDE_DIRS	+=	-I include/zappy/map/
INCLUDE_DIRS	+=	-I include/zappy/teams/

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	$(INCLUDE_DIRS)

LDFLAGS	+=	-lm
LDFLAGS	+=	-L ../library/
LDFLAGS	+=	-l criterion --coverage

LDLIBS	+=	-llist
LDLIBS	+=	-lmini
LDLIBS	+=	-lnet

NAME	=	zappy_server

TEST_NAME	=	unit_tests

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(OBJ)
	@make -C ../library/
	@$(CC) -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	@$(DELETE_FILE) $(MAIN_OBJ)
	@$(DELETE_FILE) $(OBJ)
	@$(DELETE_FILE) $(TEST_OBJ)

fclean:	clean
	@$(DELETE_FILE) $(NAME)
	@$(DELETE_FILE)	$(TEST_NAME)
	@$(DELETE_FILE) *.gcda
	@$(DELETE_FILE) *.gcno

tests_run: $(OBJ) $(SOURCE_OBJ)
	@make -C ../library/
	@$(CC) -o $(TEST_NAME) $(SOURCE) $(TEST_SOURCE) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
	@./unit_tests
	@gcovr
	@gcovr --branches

re:	fclean all

.PHONY: all $(NAME) clean fclean re
