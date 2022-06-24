/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>

void redirect_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

#include "server/server.h"

#include "options/options.h"

Test(options_tests, global, .init = redirect_std)
{
    int ac = 13;
    char *av[13] = {
        "./zappy_server",
        "-p", "4243",
        "-x", "10",
        "-y", "10",
        "-n", "martin victor",
        "-c", "2",
        "-f", "10",
    };

    zappy_t *zappy = malloc(sizeof(zappy_t));

    if (!zappy)
        return NULL;

    zappy->options = malloc(sizeof(options_t));

    if (!zappy->options) {
        free(zappy);
        return NULL;
    }

    setup_options(zappy->options);

    if (!get_options(ac, av, zappy->options))
        return 84;
    if (!handle_options(zappy->options))
        return 84;
    if (!setup_zappy_content(zappy))
        return 84;

    debug_options(zappy->options);

    free(zappy->options);
}

Test(options_test_complementary, options_tests_help, .init = redirect_std)
{
    int ac = 3;
    char *av[2] = {
        "./zappy_server",
        "--help",
    };

    options_t *options = malloc(sizeof(options_t));

    setup_options(options);

    get_options(ac, av, options);
}

Test(options_test_complementary, options_test_error, .init = redirect_std)
{
    int ac = 13;
    char *av[13] = {
        "./zappy_server",
        "-p", "4243",
        "-x", "10",
        "-y", "-1",
        "-n", "martin victor",
        "-c", "2",
        "-f", "10",
    };
    bool status = true;

    options_t *options = malloc(sizeof(options_t));

    setup_options(options);

    get_options(ac, av, options);

    status = handle_options(options);
}

Test(options_test_complementary, options_test_invalid, .init = redirect_std)
{
    int ac = 13;
    char *av[13] = {
        "./zappy_server",
        "-p", "4243",
        "-x", "10",
        "-y", "0",
        "-n", "martin victor",
        "-c", "2",
        "-f", "10",
    };
    bool status = true;

    options_t *options = malloc(sizeof(options_t));

    setup_options(options);

    get_options(ac, av, options);

    status = handle_options(options);
}

Test(options_test_complementary, options_test_unknown, .init = redirect_std)
{
    int ac = 13;
    char *av[13] = {
        "./zappy_server",
        "-p", "4243",
        "-x", "10",
        "-v", "10",
        "-n", "martin victor",
        "-c", "2",
        "-f", "10",
    };
    bool status = true;

    options_t *options = malloc(sizeof(options_t));

    setup_options(options);

    get_options(ac, av, options);

    status = handle_options(options);
}

Test(resource_tests, resource_map)
{
    int ac = 13;
    char *av[13] = {
        "./zappy_server",
        "-p", "4243",
        "-x", "10",
        "-y", "10",
        "-n", "martin victor",
        "-c", "2",
        "-f", "10",
    };

    float number_of_resources = 0.0;
    zappy_t *zappy = init_zappy();

    setup_options(zappy->options);

    if (!get_options(ac, av, zappy->options))
        return 84;
    if (!handle_options(zappy->options))
        return 84;
    if (!setup_zappy_content(zappy))
        return 84;


    for (int index = 0; index < NB_ITEMS ; index += 1)
        number_of_resources += zappy->resources[index].quantity;

    zappy->map->ratio = number_of_resources / zappy->map->size;

    fill_map(zappy->map, zappy->resources);

    debug_map(zappy->map, zappy->resources);

    free_map(zappy->map);
    free_resources(zappy->resources);

    free(zappy);
}

Test(elevation_tests, elevation_steps_setup)
{
    int ac = 13;
    char *av[13] = {
        "./zappy_server",
        "-p", "4243",
        "-x", "10",
        "-y", "10",
        "-n", "martin victor",
        "-c", "2",
        "-f", "10",
    };

    float number_of_resources = 0.0;
    zappy_t *zappy = init_zappy();

    setup_options(zappy->options);

    if (!get_options(ac, av, zappy->options))
        return 84;
    if (!handle_options(zappy->options))
        return 84;
    if (!setup_zappy_content(zappy))
        return 84;


    for (int index = 0; index < NB_ITEMS ; index += 1)
        number_of_resources += zappy->resources[index].quantity;

    zappy->map->ratio = number_of_resources / zappy->map->size;

    fill_map(zappy->map, zappy->resources);

    setup_elevation_processus(zappy);

    debug_map(zappy->map, zappy->resources);
    debug_elevation(zappy->elevation);

    free_map(zappy->map);
    free_resources(zappy->resources);
    free_elevation(zappy->elevation);

    free(zappy);
}
