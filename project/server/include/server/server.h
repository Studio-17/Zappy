/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdio.h>
    #include <string.h> //strlen
    #include <stdlib.h>
    #include <errno.h>
    #include <unistd.h>    //close
    #include <arpa/inet.h> //close
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

    #include "zappy/map/map.h"

    #include "options/options.h"

    #include "server/client/client.h"

    #define MESSAGE_SIZE 512

typedef struct server_socket_s {
    int server;
    int *client;
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
    server_socket_t *ss;
    server_socket_descriptor_t *sd;
} server_t;

void create_server(server_t *server, options_t *options);

// SETUP SERVER
void setup_server(server_t *server, options_t *options);
void initialise_all_clients_sockets(server_t *server);
void create_server_socket(server_t *server);
void allow_multiple_connections(server_t *server);

// CONNECT SERVER
void configure_socket_type(server_t *server);
void bind_socket_to_server(server_t *server);

// CONNECT CLIENT
void connect_client(server_t *server);
void clear_socket_set(server_t *server);
void add_server_socket_to_set(server_t *server);
void add_client_socket_to_set(server_t *server);
bool wait_for_connections(server_t *server);
void add_client_to_server(server_t *server, int client_socket);

// HANDLE SERVER
void handle_server(server_t *server);
void client_deconnected(server_t *server, int client_socketn);
void client_sent_request(server_t *server, int client_socket, char *command);

// void send_response(server_t *server, int client_socket, char *message);
// void get_request(int client_socket)

void debug_server(server_t *server);
void free_server(server_t *server);

#endif /* !SERVER_H_ */
