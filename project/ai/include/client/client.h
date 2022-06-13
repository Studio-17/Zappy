/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include <string.h>
    #include <stdbool.h>
    #include <inttypes.h>

    #include <sys/socket.h>
    #include <netdb.h>
    #include <arpa/inet.h>

    #include "options/options.h"

typedef struct informations_s {
    int port;
    char *address;
} informations_t;

typedef struct client_s {
    int socket;
    struct sockaddr_in server;
    informations_t *informations;
} client_t;

void setup_client(client_t *client, options_t *options);
void connect_client(client_t *client, char *team_name);

int handle_client(client_t *client);

void debug_client(client_t *client);
void free_client(client_t *client);

#endif /* !CLIENT_H_ */
