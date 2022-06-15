/*
** EPeITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** response
*/

#ifndef RESPONSE_H_
    #define RESPONSE_H_

    #include <stdbool.h>

    #include "server/server.h"

enum RESPONSE {
    OK,
    KO,

    TILES_LIST,
    INVENTORY_LIST,

    VALUE,
    OK_KO,
    DEAD,

    ELEVATION_UNDERWAY,
    CURRENT_LEVEL,
};

// AI_RESPONSE

enum RESPONSE set_player_position(void);

enum RESPONSE get_player_surroundings(void);
enum RESPONSE get_player_inventory(void);

enum RESPONSE send_message(void);

enum RESPONSE get_team_slots(void);
enum RESPONSE spawn_new_player(void);

enum RESPONSE eject_player(void);

enum RESPONSE kill_player(void);

enum RESPONSE take_object(void);
enum RESPONSE set_object(void);

enum RESPONSE start_incantation(void);

// RESPONSE

typedef struct response_ai_struct {
    enum RESPONSE response;
    int (*func)();
} response_ai;

void response_ok(server_t *server, void *data);
void response_ko(server_t *server, void *data);

void response_ok_ko(server_t *server, void *data);

void response_tiles(server_t *server, void *data);
void response_inventory(server_t *server, void *data);

void response_value(server_t *server, void *data);

void response_dead(server_t *server, void *data);

typedef struct response_elevation_struct {
    bool status;
    int level;
} response_elevation;

void response_elevation_underway(server_t *server, void *data);

// GUI_RESPONSE

// typedef struct response_gui_struct {
//     enum RESPONSE response;
//     int (*func)();
// } response_gui;

// int response_ok(void);

// static const response_gui response_gui_list[] = {
//     {OK, &response_ok},
// };

#endif /* !RESPONSE_H_ */
