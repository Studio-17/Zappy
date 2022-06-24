/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** gui_update
*/

#ifndef GUI_UPDATE_H_
#define GUI_UPDATE_H_

#include "server.h"

enum COMMANDS_GUI {
    MAP_SIZE,
    CONTENT_TILE,
    CONTENT_MAP,
    NAME_OF_TEAMS,
    PLAYER_CONNECTED,
    PLAYER_POSITION,
    PLAYER_LEVEL,
    PLAYER_INVENTORY,
    TIME_UNIT,
    TIME_UNIT_MODIFICATION,
    PLAYER_ORIENTATION,
    NB_COMMANDS_GUI
};

typedef void (*gui_update_handler)(zappy_t *, void *);

typedef struct gui_update_s {
    enum COMMANDS_GUI type;
    gui_update_handler handler;
} gui_update_t;

void gui_update_map_size(zappy_t *zappy);
void gui_update_map_content(zappy_t *zappy);
void gui_update_tile_content(zappy_t *zappy, position_t tile);
void gui_update_team_names(zappy_t *zappy);
void gui_update_player_connected(zappy_t *zappy, int data_to_update);
void gui_update_player_position(zappy_t *zappy, int player_index);
void gui_update_player_level(zappy_t *zappy, int player_index);
void gui_update_player_inventory(zappy_t *zappy, int player_index);
void gui_update_player_orientation(zappy_t *zappy, int player_index);

#endif /* !GUI_UPDATE_H_ */
