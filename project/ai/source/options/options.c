/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** options
*/

#include "options/options.h"
#include "options/usage.h"

#include "tools/tools.h"

void setup_options(options_t *options)
{
    options->port = -1;
    options->name = NULL;
    options->machine = "localhost";
}

int get_options(int ac, char **av, options_t *options)
{
    int opt = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'e'},
        {"port", required_argument, 0, 'p'},
        {"name", required_argument, 0, 'n'},
        {"machine", optional_argument, 0, 'h'},
        {0, 0, 0, 0}};

    int long_index = 0;
    while ((opt = getopt_long(ac, av, "hp:n:m:",
                              long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'e':
            print_usage(OPTIONS_ERROR_NONE);
            return (EXIT_FAILURE);
        case 'p':
            options->port = my_atoi(optarg);
            break;
        case 'n':
            options->name = optarg;
            break;
        case 'm':
            options->machine = optarg;
            break;
        default:
            print_usage(INVALID_OPTION);
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

int handle_options(options_t *options)
{
    if (options->port == -1 || options->name == NULL)
    {
        print_usage(MISSING_OPTION);
        return (EXIT_FAILURE);
    }
    if (options->port == 0 || options->name == NULL ||
        options->machine == NULL)
    {
        print_usage(INVALID_OPTION);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

void debug_options(options_t *options)
{
    printf("[DEBUG] options->port: %d\n", options->port);
    printf("[DEBUG] options->names: %s\n", options->name);
    printf("[DEBUG] options->machine: %s\n", options->machine);
}

void free_options(options_t *options)
{
    free(options);
}
