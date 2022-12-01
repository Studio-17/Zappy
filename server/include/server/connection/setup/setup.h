/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** setup
*/

#ifndef SETUP_H_
#define SETUP_H_

#include "server/server.h"

bool setup_server(server_t *server, options_t *options);
void create_server_socket(server_t *server);
void allow_multiple_connections(server_t *server);

#endif /* !SETUP_H_ */
