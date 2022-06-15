/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** request
*/

#include "netlib.h"

char *get_request(int socket)
{
    char *message = malloc(sizeof(char) * 2048);

    if (read(socket, message, sizeof(char) * 2048) == -1)
        perror("read");

    return (message);
}

void send_request(int socket, char *message)
{
    write(socket, message, strlen(message));
}
