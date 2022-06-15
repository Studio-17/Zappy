##
## EPITECH PROJECT, 2022
## B-YEP-410-PAR-4-1-zappy-martin.vanaud
## File description:
## Makefile
##


all:	libraries zappy_server zappy_gui zappy_ai

zappy_ai:
	make -C ai/

libraries:
	make -C library/

zappy_gui:
	make -C gui/

zappy_server:
	make -C server/

clean:
	make clean -C ai/
	make clean -C gui/
	make clean -C library/
	make clean -C server/

fclean:	clean
	make fclean -C ai/
	make fclean -C gui/
	make fclean -C library/
	make fclean -C server/

tests_run:
	make tests_run -C server/

re:	fclean all

.PHONY:	all libraries zappy_server zappy_gui zappy_ai tests_run