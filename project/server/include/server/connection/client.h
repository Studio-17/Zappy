/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

enum CLIENT_TYPE {
    AI,
    GRAPH,
    NB_TYPES,
};

typedef struct client_s {
    int sockfd;
    int client_nb;
    enum CLIENT_TYPE type;
    // struct sockaddr_in addr;
} client_t;

#endif /* !CLIENT_H_ */
