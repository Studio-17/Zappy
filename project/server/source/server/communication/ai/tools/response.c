/*
** EPITECH PROJECT, 2022
** project
** File description:
** response
*/

#include <stdio.h>
#include <stdbool.h>

void ai_response_ok_ko(int socket, bool status)
{
    if (status)
        dprintf(socket, "ok\n");
    else
        dprintf(socket, "ko\n");
}