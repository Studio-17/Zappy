##
## EPITECH PROJECT, 2022
## B-YEP-410-PAR-4-1-zappy-martin.vanaud
## File description:
## Makefile
##

CXX	=	g++

COPY	=	cp -f
COPY_FILE	=	$(COPY)
COPY_DIR	=	$(COPY) -r

DELETE	=	rm -f
DELETE_FILE	=	$(DELETE)
DELETE_DIR	=	$(DELETE) -r

LIBRARIES_PATH	=	../../library

MAIN_SOURCE	=	Source/Main.cpp			\

SOURCE	=	Source/Client/Client.cpp								\
			Source/Errors/Errors.cpp								\
			Source/Errors/ErrorsModules/Options/OptionsErrors.cpp	\
			Source/Errors/ErrorsModules/Client/ClientErrors.cpp		\
			Source/Options/Options.cpp								\

MAIN_OBJ	=	$(MAIN_SOURCE:.cpp=.o)

OBJ	=	$(SOURCE:.cpp=.o)

INCLUDE_DIRS	+=	-I $(LIBRARIES_PATH)/include/
INCLUDE_DIRS	+=	-I Source/
INCLUDE_DIRS	+=	-I Source/Client/
INCLUDE_DIRS	+=	-I Source/Errors/
INCLUDE_DIRS	+=	-I Source/Errors/ErrorsModules/Client/
INCLUDE_DIRS	+=	-I Source/Errors/ErrorsModules/Options/
INCLUDE_DIRS	+=	-I Source/Options/

CXXFLAGS	+=	-W -Wall -Wextra
CXXFLAGS	+=	$(INCLUDE_DIRS)

LDFLAGS	+=	-lm
LDFLAGS	+=	-L $(LIBRARIES_PATH)/

LDLIBS	+=	-llist
LDLIBS	+=	-lmini
LDLIBS	+=	-lnet

NAME	=	zappy_ai

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(OBJ)
	@make -C $(LIBRARIES_PATH)/
	@$(CXX) -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	@$(DELETE_FILE) $(MAIN_OBJ)
	@$(DELETE_FILE) $(OBJ)

fclean:	clean
	@$(DELETE_FILE) $(NAME)

re:	fclean all

.PHONY: all $(NAME) clean fclean re
