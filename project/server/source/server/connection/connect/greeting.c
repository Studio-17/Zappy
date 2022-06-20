/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** greeting
*/

#include "netlib.h"
#include "protocol/greeting.h"
#include "protocol/player.h"

#include "server/server.h"
#include "server/communication/request/request.h"

static void ai_protocol(zappy_t *zappy, int client_socket)
{
    request_payload_t info_client_request = get_request(client_socket);
    post_response_client_number(client_socket, (response_client_number_t) {true, zappy->server->clients});

    player_t player = (player_t) {.id = zappy->server->clients, .level = 1, .orientation = 0, .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height}};
    zappy->client[zappy->server->clients] = (ai_client_t){client_socket, zappy->server->clients, AI, player};

    get_map_informations(zappy, client_socket);
}

static void gui_protocol(zappy_t *zappy, int client_socket)
{
    request_payload_t info_client_request = get_request(client_socket);
    post_response_client_number(client_socket, (response_client_number_t) {true, zappy->server->clients});

    zappy->server->gui = client_socket;
    zappy->server->is_gui_connected = true;

    get_map_informations(zappy, client_socket);
}

static void post_welcome(zappy_t *zappy, int socket)
{
    write(socket, "WELCOME\n", strlen("WELCOME\n"));
}

static void get_team_name(zappy_t *zappy, int socket)
{
    char team_name[256];

    if (read(socket, &team_name, sizeof(team_name)) < 0)
        perror("get_team_name read");

    if (strcmp(team_name, "GRAPHIC\n") == 0)
        printf("%s\n", "this is a graphic client");
    else
        printf("%s\n", "this is an ai client");

}

static void post_client_num(zappy_t *zappy, int socket)
{
    char *client_num = my_itoa(zappy->server->clients);
    client_num = strcat(client_num, "\n");

    write(socket, &client_num, sizeof(&client_num));
}

static void post_map_dimensions(zappy_t *zappy, int socket)
{
    char *map_dimension = strcat(" ", my_itoa(zappy->map->height));
    map_dimension = strcat(" ", strcat(map_dimension, " "));
    map_dimension = strcat(map_dimension, my_itoa(zappy->map->width));
    map_dimension = strcat(map_dimension, "\n");

    write(socket, &map_dimension, sizeof(map_dimension));
}

void greeting_protocol(zappy_t *zappy, int client_socket)
{
    post_welcome(zappy, client_socket);

    get_team_name(zappy, client_socket);

    post_client_num(zappy, client_socket);

    post_map_dimensions(zappy, client_socket);
}
