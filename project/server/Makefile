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

SOURCE	=	source/server/communication/request/request.c		\
			source/server/communication/response/response.c		\
			source/server/server.c								\
			source/errors/errors.c								\
			source/options/options.c							\
			source/options/usage.c								\
			source/zappy/map/map.c								\
			source/zappy/map/resources.c						\
			source/tools/list.c									\
			source/tools/tools.c								\

MAIN_OBJ	=	$(MAIN_SOURCE:.c=.o)

OBJ	=	$(SOURCE:.c=.o)

INCLUDE_DIRS	+=	-I include/
INCLUDE_DIRS	+=	-I include/server/
INCLUDE_DIRS	+=	-I include/server/communication/
INCLUDE_DIRS	+=	-I include/server/communication/request/
INCLUDE_DIRS	+=	-I include/server/communication/response/
INCLUDE_DIRS	+=	-I include/server/connection/
INCLUDE_DIRS	+=	-I include/errors/
INCLUDE_DIRS	+=	-I include/options/
INCLUDE_DIRS	+=	-I include/zappy/
INCLUDE_DIRS	+=	-I include/zappy/elevation/
INCLUDE_DIRS	+=	-I include/zappy/vision/
INCLUDE_DIRS	+=	-I include/zappy/map/
INCLUDE_DIRS	+=	-I include/zappy/teams/
INCLUDE_DIRS	+=	-I include/tools/

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	$(INCLUDE_DIRS)
CFLAGS	+=	-lm

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
