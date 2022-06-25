/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** player
*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include "netlib.h"

/* PLAYER_CONNECTED */
typedef struct request_payload_player_connected_s {
    int data; // I DONT KNOW
} request_payload_player_connected_t;

typedef struct response_payload_player_connected_s {
    int id;
    int level;
    int orientation;
    position_t position;
    char team_name[50];
} response_payload_player_connected_t;

request_payload_player_connected_t get_request_player_connected(int socket);
void post_request_player_connected(int socket, request_payload_player_connected_t request);

response_payload_player_connected_t get_response_player_connected(int socket);
void post_response_player_connected(int socket, response_payload_player_connected_t response);


/* PLAYER_POSITION */
typedef struct request_payload_player_position_s {
    int player_id;
} request_payload_player_position_t;

typedef struct response_payload_player_position_s {
    int player_id;
    // int orientation;
    position_t position;
    int orientation;
} response_payload_player_position_t;

void post_response_player_position(int socket, response_payload_player_position_t response);

request_payload_player_position_t get_request_player_position(int socket);
void post_request_player_position(int socket, request_payload_player_position_t request);


/* PLAYER_LEVEL */
typedef struct request_payload_player_level_s {
    int player_id;
} request_payload_player_level_t;

typedef struct response_payload_player_level_s {
    int player_id;
    int level;
} response_payload_player_level_t;

void post_response_player_level(int socket, response_payload_player_level_t response);

request_payload_player_level_t get_request_player_level(int socket);
void post_request_player_level(int socket, request_payload_player_level_t request);


/* PLAYER_INVENTORY */
typedef struct request_payload_player_inventory_s {
    int player_id;
} request_payload_player_inventory_t;

typedef struct response_payload_player_inventory_s {
    int player_id;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int food;
} response_payload_player_inventory_t;

void post_response_player_inventory(int socket, response_payload_player_inventory_t response);

request_payload_player_inventory_t get_request_player_inventory(int socket);
void post_request_player_inventory(int socket, request_payload_player_inventory_t request);

/* PLAYER ORIENTATION */

typedef struct request_payload_player_orientation_s {
    int player_id;
} request_payload_player_orientation_t;

typedef struct response_payload_player_orientation_s {
    int player_id;
    int orientation;
} response_payload_player_orientation_t;

void post_response_player_orientation(int socket, response_payload_player_orientation_t response);


typedef struct response_payload_player_dead_s {
    int player_id;
} response_payload_player_dead_t;

void post_response_player_dead(int socket, response_payload_player_dead_t response);

typedef struct response_payload_player_start_incantation_s {
    int player_id;
} response_payload_player_start_incantation_t;

void post_response_player_start_incantation(int socket, response_payload_player_start_incantation_t response);

typedef struct response_payload_player_end_incantation_s {
    bool success;
    int player_id;
    int player_level;
} response_payload_player_end_incantation_t;

void post_response_player_end_incantation(int socket, response_payload_player_end_incantation_t response);

#endif /* !PLAYER_H_ */
