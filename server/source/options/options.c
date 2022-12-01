/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** options
*/

#include "options/options.h"
#include "options/usage.h"

#include "minilib.h"

void setup_options(options_t *options)
{
    options->port = -1;
    options->width = -1;
    options->height = -1;
    options->names = NULL;
    options->team_names = NULL;
    options->clients_nb = -1;
    options->freq = 100;
}

bool get_options(int ac, char * const *av, options_t *options)
{
    int opt = 0;
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"port", required_argument, 0, 'p'},
        {"width", required_argument, 0, 'x'},
        {"heigth", required_argument, 0, 'y'},
        {"nameX", required_argument, 0, 'n'},
        {"clients_nb", required_argument, 0, 'c'},
        {"freq", optional_argument, 0, 'f'},
        {0, 0, 0, 0}};
    int long_index = 0;

    int index = 0;
    char *team_names = NULL;

    while ((opt = getopt_long(ac, av, "hp:x:y:n:c:f:",
                              long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_usage(OPTIONS_ERROR_NONE);
            return false;
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
            for (index = optind -1; index < ac; index += 1){
                if (av[index][0] != '-') {

                    if (!team_names)
                        team_names = strdup(av[index]);
                    else {
                        team_names = realloc(team_names, strlen(team_names) + strlen(av[index]) + 2);
                        team_names = strcat(team_names, " ");
                        team_names = strcat(team_names, av[index]);
                    }

                } else {
                    break;
                }
            }
            optind = index;
            options->names = strdup(team_names);
            free(team_names);
            break;
        case 'c':
            options->clients_nb = my_atoi(optarg);
            break;
        case 'f':
            options->freq = my_atoi(optarg);
            break;
        default:
            print_usage(INVALID_OPTION);
            return false;
        }
    }
    return true;
}

bool handle_options(options_t *options)
{
    if (options->port == -1 || options->width == -1 ||
        options->height == -1 || options->names == NULL ||
        options->clients_nb == -1)
    {
        print_usage(MISSING_OPTION);
        return false;
    }
    else if (options->port == 0 || options->width == 0 ||
        options->height == 0 || options->names == NULL ||
        options->clients_nb == 0)
    {
        print_usage(INVALID_OPTION);
        return false;
    }
    else if (options->width < 10 || options->width > 30)
    {
        printf("\n%s\n\n", "-x option only accepts integer values between 10 and 30");
        print_usage(OPTIONS_ERROR_NONE);
        return false;
    }
    else if (options->height < 10 || options->height > 30)
    {
        printf("\n%s\n\n", "-y option only accepts integer values between 10 and 30");
        print_usage(OPTIONS_ERROR_NONE);
        return false;
    }
    else if (options->freq <= 1 || options->freq >= 10000)
    {
        printf("\n%s\n\n", "-f option only accepts integer values between 2 and 10000");
        print_usage(OPTIONS_ERROR_NONE);
        return false;
    }

    return true;
}

void debug_options(options_t *options)
{
    printf("[DEBUG] options->port: %d\n", options->port);
    printf("[DEBUG] options->width: %d\n", options->width);
    printf("[DEBUG] options->height: %d\n", options->height);
    printf("[DEBUG] options->names: %s\n", options->names);
    printf("[DEBUG] options->clients_nb: %d\n", options->clients_nb);
    printf("[DEBUG] options->freq: %d\n", options->freq);
}

void free_options(options_t *options)
{
    free_arr(options->team_names);
    free(options);
}
