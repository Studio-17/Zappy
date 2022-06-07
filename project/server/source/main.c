/*
** EPITECH PROJECT, 2022
** B-EPI-000-PAR-0-0-projectname-user.email
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "options/options.h"

int main(int ac, char **av)
{
    options_t *options = malloc(sizeof(options_t));

    setup_options(options);

    get_options(ac, av, options);

    debug_options(options);

    free_options(options);

    return (EXIT_SUCCESS);
}
