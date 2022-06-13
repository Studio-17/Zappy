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

    #include "server/connection/client.h"

    #define MAX_CLIENTS 10

typedef struct informations_s {
    char *address;
    int server_port;
    int ai_port;
    int gui_port;
} informations_t;

typedef struct server_s {
    int sockfd;
    unsigned int port;
    int max_clients;
    fd_set readfds;
    struct sockaddr_in sockaddr;
    client_t *clients;
} server_t;

// typedef struct server_request_s {
//     char *request;
//     enum CLIENT_TYPE type;
//     enum RESPONSE (*response)();
// } server_request_t;

int create_server(server_t *server, options_t *options);

void setup_server(server_t *server);
void connect_server(server_t *server, char *team_name);

int handle_server(server_t *server);

void debug_server(server_t *server);
void free_server(server_t *server);

#endif /* !SERVER_H_ */
