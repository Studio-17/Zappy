/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** map
*/

#ifndef MAP_H_
#define MAP_H_

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

#endif /* !MAP_H_ */
