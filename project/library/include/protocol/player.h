/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** player
*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include "netlib.h"

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



typedef struct request_payload_player_inventory_s {
    int player_id;
} request_payload_player_inventory_t;

typedef struct response_payload_player_inventory_s {
    bool status;
    int player_id;
    // inventory_t inventory; // TO BE DEFINED
} response_payload_player_inventory_t;

void post_response_player_inventory(int socket, response_payload_player_inventory_t response);

request_payload_player_inventory_t get_request_player_inventory(int socket);
void post_request_player_inventory(int socket, request_payload_player_inventory_t request);

#endif /* !PLAYER_H_ */
