/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** header
*/

#include "netlib.h"

void post_header(int socket, payload_header_t header)
{
    write(socket, &header, sizeof(payload_header_t));
}

payload_header_t get_header(int socket)
{
    payload_header_t header;

    if (read(socket, &header, sizeof(payload_header_t)) < 0)
        perror("get_header read");

    return (header);
}
