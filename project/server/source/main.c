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
    int options_status = 1;
    options_t *options = malloc(sizeof(options_t));

    setup_options(options);

    options_status = get_options(ac, av, options);
    if (options_status == 1)
        return (EXIT_FAILURE);

    options_status = handle_options(options);
    if (options_status == 1)
        return (EXIT_FAILURE);

    free_options(options);

    return (EXIT_SUCCESS);
}
