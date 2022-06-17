/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** connect
*/

#ifndef CONNECT_H_
#define CONNECT_H_

#include "server/server.h"

void connect_client(server_t *server);
void clear_socket_set(server_t *server);
void add_server_socket_to_set(server_t *server);
void add_client_socket_to_set(server_t *server);
void wait_for_connections(server_t *server);
void add_client_to_server(server_t *server, int client_socket);

void configure_socket_type(server_t *server);
void bind_socket_to_server(server_t *server);

#endif /* !CONNECT_H_ */
