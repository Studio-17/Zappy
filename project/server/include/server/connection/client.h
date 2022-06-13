/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include "tools/list.h"

enum CLIENT_TYPE {
    AI,
    NB_TYPES,
};

typedef struct client_s {
    int sockfd;
    int client_nb;
    enum CLIENT_TYPE type;
    // struct sockaddr_in addr;
    list_t list;
} client_t;

#endif /* !CLIENT_H_ */
