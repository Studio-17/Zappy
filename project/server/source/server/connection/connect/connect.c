/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** connect
*/

#include "netlib.h"
#include "protocol/greeting.h"
#include "protocol/player.h"

#include "server/server.h"
#include "server/communication/request/request.h"

static bool team_name_allowed(char *client_names, char *team_name)
{
    if (strcmp(team_name, "GRAPHIC") == 0)
        return (true);

    char **names = my_strtok(client_names, ' ');

    for (int index = 0; names[index]; index += 1) {
        if (strcmp(names[index], team_name) == 0) {
            return (true);
        }
    }
    return (false);
}

void get_client_team_name(zappy_t *zappy, int client_socket)
{
    // GET CLIENT NAME & SEND OK/KO
    if (zappy->server->clients > zappy->options->clients_nb) {
        post_response(client_socket, (response_payload_t) {false, "KO\n"});
        close(client_socket);
        exit(0);
    }
    request_payload_t team_name_request = get_request(client_socket);
    printf("%s\n", team_name_request.payload);
    if (team_name_allowed(zappy->options->names, team_name_request.payload)) {
        post_response(client_socket, (response_payload_t) {true, "OK\n"});
    } else {
        post_response(client_socket, (response_payload_t) {false, "KO\n"});
        close(client_socket);
        return;
    }
}

void get_map_informations(zappy_t *zappy, int client_socket)
{
    request_payload_t info_map_request = get_request(client_socket);
    post_response_map(client_socket, (response_payload_map_t) {true, zappy->options->width, zappy->options->height});
}
