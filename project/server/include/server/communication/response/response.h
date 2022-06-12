/*
** EPeITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** response
*/

#ifndef RESPONSE_H_
    #define RESPONSE_H_

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

void send_response(void);

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

int response_ok(void);
int response_ko(void);
int response_ok_ko(void);
int response_tiles(void);
int response_inventory(void);
int response_value(void);
int response_dead(void);
int response_elevation_underway(void);

static const response_ai response_ai_list[] = {
    {OK, &response_ok},
    {OK, &response_ok},
    {OK, &response_ok},
    {TILES_LIST, &response_tiles},
    {INVENTORY_LIST, &response_inventory},
    {OK, &response_ok},
    {VALUE, &response_value},
    {OK, &response_ok},
    {OK_KO, &response_ok_ko},
    {DEAD, &response_dead},
    {OK_KO, &response_ok_ko},
    {OK_KO, &response_ok_ko},
    {ELEVATION_UNDERWAY, &response_elevation_underway},
};

// GUI_RESPONSE

typedef struct response_gui_struct {
    enum RESPONSE response;
    int (*func)();
} response_gui;

int response_ok(void);

static const response_gui response_gui_list[] = {
    {OK, &response_ok},
};

#endif /* !RESPONSE_H_ */
