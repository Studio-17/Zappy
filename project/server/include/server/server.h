/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>

    #include "netlib.h"

    #include "zappy/map/map.h"
    #include "zappy/map/resources.h"

    #include "options/options.h"

    #include "server/server_struct.h"

    #include "server/client/client.h"
    #include "server/connection/setup/setup.h"

typedef struct zappy_s {
    options_t *options;
    server_t *server;
    map_t *map;
    resources_t *ressources;
} zappy_t;

void create_server(zappy_t *zappy);
void client_deconnected(zappy_t *zappy, int client_socketn);

void handle_client(zappy_t *zappy);

void connect_client(zappy_t *zappy);
void clear_socket_set(server_t *server);
void add_server_socket_to_set(server_t *server);
void add_client_socket_to_set(server_t *server);
void wait_for_connections(server_t *server);
void add_client_to_server(server_t *server, int client_socket);

void debug_server(zappy_t *zappy);
void free_server(zappy_t *zappy);

void configure_socket_type(server_t *server);
void bind_socket_to_server(server_t *server);


#endif /* !SERVER_H_ */
