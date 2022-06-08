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

enum OPTIONS_ERROR {
    MISSING_OPTION = -1,
    INVALID_OPTION = 0,
    OPTIONS_ERROR_NONE = 1,
};

typedef struct options_error_s {
    int error_code;
    char *error_message;
} options_error_t;

static const options_error_t options_error_messages[] = {
    {MISSING_OPTION, "ERROR ./zappy_server - missing option"},
    {INVALID_OPTION, "ERROR ./zappy_server - invalid option"},
};

typedef struct options_s {
    int port;
    int width;
    int height;
    char *names;
    int clientsNb;
    int freq;
} options_t;

void setup_options(options_t *options);
int get_options(int ac, char **av, options_t *options);
int handle_options(options_t *options);
void debug_options(options_t *options);
void free_options(options_t *options);

#endif /* !OPTIONS_H_ */
