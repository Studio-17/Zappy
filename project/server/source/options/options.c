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
    options->width = -1;
    options->height = -1;
    options->names = NULL;
    options->clientsNb = -1;
    options->freq = -1;
}

int get_options(int ac, char **av, options_t *options)
{
    int opt = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"port", required_argument, 0, 'p'},
        {"width", required_argument, 0, 'x'},
        {"heigth", required_argument, 0, 'y'},
        {"nameX", required_argument, 0, 'n'},
        {"clientsNb", required_argument, 0, 'c'},
        {"freq", required_argument, 0, 'f'},
        {0, 0, 0, 0}};

    int long_index = 0;
    while ((opt = getopt_long(ac, av, "hp:x:y:n:c:f:",
                              long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_usage(OPTIONS_ERROR_NONE);
            break;
        case 'p':
            options->port = my_atoi(optarg);
            break;
        case 'x':
            options->width = my_atoi(optarg);
            break;
        case 'y':
            options->height = my_atoi(optarg);
            break;
        case 'n':
            options->names = optarg;
            break;
        case 'c':
            options->clientsNb = my_atoi(optarg);
            break;
        case 'f':
            options->freq = my_atoi(optarg);
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
    if (options->port == -1 || options->width == -1 ||
        options->height == -1 || options->names == NULL ||
        options->clientsNb == -1 || options->freq == -1)
    {
        print_usage(MISSING_OPTION);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

void debug_options(options_t *options)
{
    printf("port: %d\n", options->port);
    printf("width: %d\n", options->width);
    printf("height: %d\n", options->height);
    printf("names: %s\n", options->names);
    printf("clientsNb: %d\n", options->clientsNb);
    printf("freq: %d\n", options->freq);
}

void free_options(options_t *options)
{
    free(options->names);
    free(options);
}
