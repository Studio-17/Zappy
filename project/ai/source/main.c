/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** main
*/

#include "options/options.h"

#include "client/client.h"

int main(int ac, char **av)
{
    int options_status = 1;
    options_t *options = malloc(sizeof(options_t));

    setup_options(options);

    options_status = get_options(ac, av, options);
    if (options_status == EXIT_FAILURE)
        return (EXIT_FAILURE);

    options_status = handle_options(options);
    if (options_status == EXIT_FAILURE)
        return (EXIT_FAILURE);

    client_t *client = malloc(sizeof(client_t));

    setup_client(client, options);

    connect_client(client, options->name);

    free_options(options);

    return (EXIT_SUCCESS);
}
