/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** usage
*/

#ifndef USAGE_H_
    #define USAGE_H_

    #include <stdio.h>

    #define USAGE_MESSAGE "./zappy_server --help\n \
USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\n \
    port      is the port number\n \
    width     is the width of the world\n \
    height    is the height of the world\n \
    nameX     is the name of the team X\n \
    clientsNb is the number of authorized clients per team\n \
    freq      is the reciprocal of time unit for execution of actions\n"

void print_usage(int error_code);

#endif /* !USAGE_H_ */
