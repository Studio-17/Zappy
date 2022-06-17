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

    #include "options/options.h"

    #include "server/server_struct.h"

    #include "server/client/client.h"
    #include "server/connection/setup/setup.h"
    #include "server/connection/connect/connect.h"

void create_server(server_t *server, options_t *options);
void client_deconnected(server_t *server, int client_socketn);

void handle_client(server_t *server);

void debug_server(server_t *server);
void free_server(server_t *server);

#endif /* !SERVER_H_ */
