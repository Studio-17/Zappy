/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    // #include <stdio.h>
    // #include <string.h>
    // #include <stdlib.h>
    // #include <errno.h>
    // #include <unistd.h>
    // #include <sys/types.h>
    // #include <sys/socket.h>

    #include <math.h>

    #include "netlib.h"

    #include "protocol/map.h"

    #include "client/client.h"

    #include "options/options.h"

    #include "server/server_struct.h"

    #include "server/client/client.h"
    #include "server/connection/setup/setup.h"


    #define RESOURCE_QUANTITY(width, height, density) (width * height * density)

enum ITEM {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    NB_ITEMS,
};

typedef struct resources_s {
    char *name;
    enum ITEM item;
    float density;
    int quantity;
} resources_t;

resources_t *setup_resources(int width, int height);


void debug_resources(resources_t *resource);
void free_resources(resources_t *resources);

typedef struct tile_s {
    int width;
    int heigth;
    resources_t *resources;
} tile_t;

typedef struct map_s {
    int width;
    int height;
    float size;
    float ratio;
    tile_t **tiles;
} map_t;

map_t *create_map(int width, int height);

void fill_map(map_t *map, resources_t *resource);

void debug_map(map_t *map, resources_t *resources_list);
void free_map(map_t *map);

typedef struct zappy_s {
    options_t *options;
    server_t *server;
    map_t *map;
    ai_client_t *client;
    resources_t *resources;
} zappy_t;

zappy_t *init_zappy(void);
bool setup_zappy_content(zappy_t *zappy);

void free_zappy(zappy_t *zappy);

void create_server(zappy_t *zappy);
bool server_loop(zappy_t *zappy);
void client_deconnected(zappy_t *zappy, int client_socketn);

void configure_socket_type(server_t *server);
void bind_socket_to_server(server_t *server);

bool connect_client(zappy_t *zappy);
void clear_socket_set(server_t *server);
void add_server_socket_to_set(server_t *server);
void add_client_socket_to_set(server_t *server);
void wait_for_connections(server_t *server);
void add_client_to_server(server_t *server, int client_socket);

bool greeting_protocol(zappy_t *zappy, int client_socket);
void setup_non_blocking_sockets(int client_socket);

void get_client_team_name(zappy_t *zappy, int client_socket);
void get_map_informations(zappy_t *zappy, int client_socket);

bool listen_clients(zappy_t *zappy);
void *gui_get_generic_request(int client_socket, int size_to_read);

void gui_handle_request(zappy_t *zappy);
bool ai_handle_request(zappy_t *zappy, int player_index);

void debug_server(server_t *server);
void free_server(server_t *server);

#endif /* !SERVER_H_ */
