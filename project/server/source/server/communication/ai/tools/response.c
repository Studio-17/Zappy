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
    dprintf(socket, (status ? "ok\n" : "ko\n"));
}