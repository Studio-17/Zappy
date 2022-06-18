/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** netlib
*/

#ifndef NETLIB_H_
    #define NETLIB_H_

    #include <unistd.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <fcntl.h>

// HEADER

typedef struct payload_header_s {
    int size;
    int type; // TO BE CAST TO ENUM type : )
} payload_header_t;

void post_header(int socket, payload_header_t header);
payload_header_t get_header(int socket);

// BASE
typedef struct request_payload {
    char payload[1024];
} request_payload_t;

void post_request(int socket, request_payload_t request);
request_payload_t get_request(int socket);

typedef struct response_payload {
    bool status;
    char payload[1024];
} response_payload_t;

void post_response(int socket, response_payload_t response);
response_payload_t get_response(int socket);

// CLIENT NUMBER
typedef struct response_client_number {
    bool status;
    int id;
} response_client_number_t;

void post_response_client_number(int socket, response_client_number_t request);

typedef struct response_payload_client_number {
    bool status;
    int client_id;
} response_payload_client_number_t;

response_payload_client_number_t get_response_client_number(int socket);

// MAP
typedef struct response_payload_map_s {
    bool status;
    int width;
    int height;
} response_payload_map_t;

response_payload_map_t get_response_map(int socket);
void post_response_map(int socket, response_payload_map_t response);

typedef struct position_s {
    int x;
    int y;
} position_t;

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

#endif /* !NETLIB_H_ */
