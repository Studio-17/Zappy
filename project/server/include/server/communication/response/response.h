/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** response
*/

#ifndef RESPONSE_H_
    #define RESPONSE_H_

enum RESPONSE {
    OK,
    KO,

    TILES,
    INVENTORY,

    VALUE,
    OK_KO,
    DEAD,

    ELEVATION_UNDERWAY,
    CURRENT_LEVEL,
};

typedef struct response_s {
    RESPONSE response;
    char *message;
} response_t;

#endif /* !RESPONSE_H_ */
