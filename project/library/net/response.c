/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** response
*/

#include "netlib.h"

char *get_response(int socket)
{
    char *message = malloc(sizeof(char) * 2048);

    if (read(socket, message, sizeof(char) * 2048) == -1)
        perror("read");

    return (message);
}

response_payload_t get_struct_response(int socket)
{
    response_payload_t response;

    if (read(socket, &response, sizeof(response_payload_t)) == -1)
        perror("read");

    return (response);
}

void send_response(int socket, char *message)
{
    write(socket, message, strlen(message));
}

void send_struct_response(int socket, response_payload_t response)
{
    write(socket, &response, sizeof(response_payload_t));
}
