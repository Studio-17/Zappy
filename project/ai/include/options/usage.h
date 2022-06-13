/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** usage
*/

#ifndef USAGE_H_
    #define USAGE_H_

    #include <stdio.h>

    #define USAGE_MESSAGE "./zappy_ai --help\n \
USAGE: ./zappy_ai -p port -n name -h machine\n \
    port is the port number\n \
    name is the name of the team\n \
    machine is the name of the machine; localhost by default\n"

void print_usage(int error_code);

#endif /* !USAGE_H_ */
