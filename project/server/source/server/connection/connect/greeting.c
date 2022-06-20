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
    get_client_team_name(zappy, client_socket);

    request_payload_t info_client_request = get_request(client_socket);
    post_response_client_number(client_socket, (response_client_number_t) {true, zappy->server->clients});

    player_t player = (player_t) {.id = zappy->server->clients, .level = 1, .orientation = 0, .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height}};
    zappy->client[zappy->server->clients] = (ai_client_t){client_socket, zappy->server->clients, AI, player};

    get_map_informations(zappy, client_socket);
}

static void gui_protocol(zappy_t *zappy, int client_socket)
{
    get_client_team_name(zappy, client_socket);

    request_payload_t info_client_request = get_request(client_socket);
    post_response_client_number(client_socket, (response_client_number_t) {true, zappy->server->clients});

    zappy->server->gui = client_socket;
    zappy->server->is_gui_connected = true;

    get_map_informations(zappy, client_socket);
}

void greeting_protocol(zappy_t *zappy, int client_socket)
{
    request_payload_t request = get_request(client_socket);
    post_response(client_socket, (response_payload_t) {true, "WELCOME\n"});

    if (strcmp(request.payload, "IA\n") == 0) {
        ai_protocol(zappy, client_socket);
    } else if (strcmp(request.payload, "GRAPHIC\n") == 0) {
        gui_protocol(zappy, client_socket);
    } else {
        // this is an error
    }
}
