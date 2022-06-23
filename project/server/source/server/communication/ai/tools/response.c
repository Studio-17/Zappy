/*
** EPITECH PROJECT, 2022
** project
** File description:
** response
*/

#include <stdlib.h>
#include <stdbool.h>

void ai_response_ok_ko(int socket, bool status)
{
    size_t message_size = 4;

    write(socket, (status ? "ok\n" : "ko\n" ), message_size);
}