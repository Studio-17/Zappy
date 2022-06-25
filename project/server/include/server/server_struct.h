/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** server_struct
*/

#ifndef SERVER_STRUCT_H_
#define SERVER_STRUCT_H_

#include <arpa/inet.h>
#include <sys/time.h>

typedef struct server_socket_s {
    int server;
    int max_client;
} server_socket_t;

typedef struct server_socket_descriptor_s {
    fd_set readfd;
    int socket_descriptor;
    int max_socket_descriptor;
} server_socket_descriptor_t;

typedef struct server_s {
    int port;
    struct sockaddr_in address;
    int address_length;
    server_socket_t *server_socket;
    server_socket_descriptor_t *socket_descriptor;

    int clients;

    int gui;
    bool is_gui_connected;
} server_t;

#endif /* !SERVER_STRUCT_H_ */
