/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** greeting
*/

#ifndef GREETING_H_
#define GREETING_H_

#include "netlib.h"

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

typedef struct response_payload_map_s {
    bool status;
    int width;
    int height;
} response_payload_map_t;

response_payload_map_t get_response_map(int socket);
void post_response_map(int socket, response_payload_map_t response);

#endif /* !GREETING_H_ */
