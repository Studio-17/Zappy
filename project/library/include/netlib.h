/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** netlib
*/

#ifndef NETLIB_H_
    #define NETLIB_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    #include <string.h>
    #include <sys/types.h>

    #include <sys/socket.h>

char *get_response(int socket);
void send_response(int socket, char *message);

char *get_request(int socket);
void send_request(int socket, char *message);

#endif /* !NETLIB_H_ */
