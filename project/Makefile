##
## EPITECH PROJECT, 2022
## B-YEP-410-PAR-4-1-zappy-martin.vanaud
## File description:
## Makefile
##


all:	zappy_server zappy_gui zappy_ai

zappy_server:
	make -C server/

zappy_gui:
	make -C gui/

zappy_ai:
	chmod +x ai/zappy_ai

clean:
	make clean -C server/
	make clean -C gui/

fclean:	clean
	make fclean -C server/
	make fclean -C gui/

re:	fclean all

.PHONY:	all zappy_server zappy_gui zappy_ai