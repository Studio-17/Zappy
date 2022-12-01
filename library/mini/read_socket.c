/*
** EPITECH PROJECT, 2022
** project
** File description:
** read_socket
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *read_in_socket(int socket)
{
    char data[24];
    char *buffer = NULL;
    bzero(data, sizeof(data));
    int read_value = read(socket, &data, sizeof(data));

    if (read_value < 0)
        perror("ai_get_generic_request read");
    buffer = malloc(sizeof(char) * read_value + 1);
    if (!buffer)
        return NULL;
    buffer[read_value] = '\0';
    strncpy(buffer, data, read_value);

    return (buffer);
}