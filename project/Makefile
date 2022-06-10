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
	make clean -C ./src/core
	make clean -C ./src/graphics/sdl2
	make clean -C ./src/graphics/ncurses

fclean:	clean
	make fclean -C ./src/core
	make fclean -C ./src/graphics/sdl2
	make fclean -C ./src/graphics/ncurses

re:	fclean all

.PHONY:	all zappy_server zappy_gui zappy_ai