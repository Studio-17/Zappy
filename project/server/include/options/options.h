/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** options
*/

#ifndef OPTIONS_H_
    #define OPTIONS_H_

    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <getopt.h>

typedef struct options_s {
    int port;
    int width;
    int height;
    char *names;
    int clientsNb;
    int freq;
} options_t;

void setup_options(options_t *options);
void get_options(int ac, char **av, options_t *options);
void debug_options(options_t *options);
void free_options(options_t *options);

#endif /* !OPTIONS_H_ */
