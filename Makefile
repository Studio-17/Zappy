##
## EPITECH PROJECT, 2022
## B-YEP-410-PAR-4-1-zappy-martin.vanaud
## File description:
## Makefile
##

all:	libraries zappy_server zappy_gui zappy_ai

zappy_ai:
	make -C client/ai/

libraries:
	make -C library/

zappy_gui:
	chmod +x client/gui/cmake.sh
	bash client/gui/cmake.sh

zappy_server:
	make -C server/

clean:
	make clean -C client/ai/
	make clean -C library/
	make clean -C server/

fclean:	clean
	make fclean -C client/ai/
	make fclean -C library/
	make fclean -C server/

tests_run:
	make tests_run -C server/

re:	fclean all

.PHONY:	all libraries zappy_server zappy_gui zappy_ai tests_run
