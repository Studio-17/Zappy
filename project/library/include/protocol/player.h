/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** player
*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include "netlib.h"

// /* MAP_SIZE */
typedef struct request_payload_map_size_s {
} request_payload_map_size_t;

typedef struct response_payload_map_size_s {
    position_t position;
} response_payload_map_size_t;

request_payload_map_size_t get_request_map_size(int socket);
void post_response_map_size(int socket, response_payload_map_size_t response);

request_payload_map_size_t get_request_map_size(int socket);
void post_request_map_size(int socket, request_payload_map_size_t request);


/* CONTENT_MAP */
typedef struct request_payload_content_map_s {
} request_payload_content_map_t;

typedef struct response_payload_content_map_s {
    response_payload_map_size_t map_size;
    response_payload_content_tile_t **content;

} response_payload_content_map_t;

void post_response_content_map(int socket, response_payload_content_map_t response);

request_payload_content_map_t get_request_content_map(int socket);
void post_request_content_map(int socket, request_payload_content_map_t request);

/* CONTENT_TILE */
typedef struct request_payload_content_tile_s {
    position_t position;
} request_payload_content_tile_t;

typedef struct response_payload_content_tile_s {
    position_t position;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    int food;
} response_payload_content_tile_t;

void post_response_content_tile(int socket, response_payload_content_tile_t response);

request_payload_content_tile_t get_request_content_tile(int socket);
void post_request_content_tile(int socket, request_payload_content_tile_t request);


/* PLAYER_CONNECTED */
typedef struct request_payload_player_connected_s {
    int data; // I DONT KNOW
} request_payload_player_connected_t;

typedef struct response_payload_player_connected_s {
    bool status;
    int id;
    int level;
    int orientation;
    position_t position;
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
    bool status;
    int player_id;
    position_t position;
} response_payload_player_position_t;

void post_response_player_position(int socket, response_payload_player_position_t response);

request_payload_player_position_t get_request_player_position(int socket);
void post_request_player_position(int socket, request_payload_player_position_t request);


/* PLAYER_LEVEL */
typedef struct request_payload_player_level_s {
    int player_id;
} request_payload_player_level_t;

typedef struct response_payload_player_level_s {
    bool status;
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
    bool status;
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

#endif /* !PLAYER_H_ */
