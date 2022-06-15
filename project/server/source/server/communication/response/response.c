/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** response
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minilib.h"

#include "server/server.h"
#include "server/communication/response/response.h"

enum RESPONSE set_player_position(void)
{
    return (KO);
}

enum RESPONSE get_player_surroundings(void)
{
    return (KO);
}
enum RESPONSE get_player_inventory(void)
{
    return (KO);
}

enum RESPONSE send_message(void)
{
    return (KO);
}

enum RESPONSE get_team_slots(void)
{
    return (KO);
}
enum RESPONSE spawn_new_player(void)
{
    return (KO);
}

enum RESPONSE eject_player(void)
{
    return (KO);
}

enum RESPONSE kill_player(void)
{
    return (KO);
}

enum RESPONSE take_object(void)
{
    return (KO);
}
enum RESPONSE set_object(void)
{
    return (KO);
}

enum RESPONSE start_incantation(void)
{
    return (KO);
}

void response_ok(server_t *server, __attribute__((unused)) void *data)
{
    send(server->ss->server, "ok\n", 3, 0);
}

void response_ko(server_t *server, __attribute__((unused)) void *data)
{
    send(server->ss->server, "ko\n", 3, 0);
}

void response_ok_ko(server_t *server, void *data)
{
    bool status = *(bool *)data;

    if (status)
        send(server->ss->server, "ok\n", 3, 0);
    else
        send(server->ss->server, "ko\n", 3, 0);
}

void response_tiles(server_t *server, __attribute__((unused)) void *data)
{
    send(server->ss->server, "Not implemented yet\n", 21, 0);
}

void response_inventory(server_t *server, __attribute__((unused)) void *data)
{
    send(server->ss->server, "Not implemented yet\n", 21, 0);
}

void response_value(server_t *server, void *data)
{
    int value = *(int *)data;
    char *message = my_itoa(value);
    strcat(message, "\n");

    send(server->ss->server, message, strlen(message), 0);
}

void response_dead(server_t *server, __attribute__((unused)) void *data)
{
    send(server->ss->server, "dead\n", 5, 0);
}

void response_elevation_underway(server_t *server, void *data)
{
    response_elevation elevation = *(response_elevation *)data;

    if (elevation.status)
    {
        char *message = "Elevation underway Current level: ";
        strcat(message, strcat(my_itoa(elevation.level), "\n"));
        send(server->ss->server, message, strlen(message), 0);
    }
    else
        send(server->ss->server, "ko\n", 3, 0);
}
