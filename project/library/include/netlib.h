/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** netlib
*/

#ifndef NETLIB_H_
    #define NETLIB_H_

    #include <unistd.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <fcntl.h>

// HEADER

enum SENDER_ID {
    SERVER,
    IA,
    GUI,
};

typedef struct payload_header_s {
    int id; // SERVER = 0, 1 = AI, 2 = GUI
    int size;
    int type; // TO BE CAST TO ENUM type : )
} payload_header_t;

void post_header(int socket, payload_header_t header);
payload_header_t get_header(int socket);

// TOOLS

typedef struct position_s {
    int x;
    int y;
} position_t;

#endif /* !NETLIB_H_ */
