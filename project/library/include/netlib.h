/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** netlib
*/

#ifndef NETLIB_H_
    #define NETLIB_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include <string.h>
    #include <stdbool.h>
    #include <sys/types.h>

    #include <sys/socket.h>

typedef struct repsonse_payload_s {
    int id;
    bool status;
    char message[256];
} response_payload_t;

typedef struct request_payload_s {
    int id;
    char command[256];
} request_payload_t;

char *get_response(int socket);
response_payload_t get_struct_response(int socket);
void send_response(int socket, char *message);
void send_struct_response(int socket, response_payload_t response);

char *get_request(int socket);
request_payload_t get_struct_request(int socket);
void send_request(int socket, char *message);
void send_struct_request(int socket, request_payload_t request);

response_payload_t get_response_payload(char *message);
response_payload_t parse_response_payload(char **payload);

request_payload_t get_request_payload(char *message);
request_payload_t parse_request_payload(char **payload);

#endif /* !NETLIB_H_ */
