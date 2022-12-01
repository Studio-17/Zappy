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

Test(setup_tests, server_setup)
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

    create_server(zappy);

    create_server_socket(zappy->server);
    allow_multiple_connections(zappy->server);

    configure_socket_type(zappy->server);

    free(zappy);
}

#include "ai_request.h"

// static bool create_player(zappy_t *zappy, int socket, char *team_name)
// {
//     player_t player = {
//         .id = zappy->server->clients,
//         .level = 1,
//         .position = (position_t){rand() % zappy->options->width, rand() % zappy->options->height},
//         .orientation = NORTH,
//         .elevation_status = NONE,
//         .resource_inventory = malloc(sizeof(inventory_resource_t) * NB_ITEMS),
//         .units = 0,
//     };

//     player.resource_inventory[FOOD].resource = FOOD;
//     player.resource_inventory[FOOD].quantity = 10;
//     for (int index = 1; index < NB_ITEMS; index += 1) {
//         player.resource_inventory[index].resource = (enum ITEM)index;
//         player.resource_inventory[index].quantity = 0;
//     }

//     zappy->client[zappy->server->clients] = (ai_client_t){
//         .socket = socket,
//         .id = 0,
//         .client_nb = zappy->server->clients,
//         .type = AI,
//         .player = player,
//         .list = NULL,
//         .team_members = 0,
//         .clock = clock(),
//     };

//     int id = zappy->options->max_clients - zappy->server->clients;

//     int team_members_connected = 0;
//     int client_nb = zappy->options->clients_nb - 0 - 1;

//     if (client_nb < 0 || id < 0)
//         return (false);

//     zappy->client[zappy->server->clients].id = id;

//     strcpy(zappy->client[zappy->server->clients].team_name, team_name);
//     zappy->client[zappy->server->clients].team_members = team_members_connected;
//     zappy->client[zappy->server->clients].client_nb = client_nb;

//     printf("client-id(server-side): %d\n", zappy->client[zappy->server->clients].id);

//     if (zappy->server->is_gui_connected)
//         gui_update_player_connected(zappy, zappy->server->clients);

//     zappy->server->clients += 1;

//     return (true);
// }


// Test(request_tests, request_ai_connect_nbr_failed)
// {
//     int ac = 13;
//     char *av[13] = {
//         "./zappy_server",
//         "-p", "4243",
//         "-x", "10",
//         "-y", "10",
//         "-n", "martin victor",
//         "-c", "2",
//         "-f", "10",
//     };

//     float number_of_resources = 0.0;
//     zappy_t *zappy = init_zappy();

//     setup_options(zappy->options);

//     if (!get_options(ac, av, zappy->options))
//         return 84;
//     if (!handle_options(zappy->options))
//         return 84;
//     if (!setup_zappy_content(zappy))
//         return 84;

//     create_player(zappy, 0, "martin");

//     ai_connect_nbr_request(zappy, NULL, zappy->server->clients);

//     free(zappy);
// }

// Test(request_tests, request_ai_connect_nbr_success)
// {
//     int ac = 13;
//     char *av[13] = {
//         "./zappy_server",
//         "-p", "4243",
//         "-x", "10",
//         "-y", "10",
//         "-n", "martin victor",
//         "-c", "2",
//         "-f", "10",
//     };

//     float number_of_resources = 0.0;
//     zappy_t *zappy = init_zappy();

//     setup_options(zappy->options);

//     if (!get_options(ac, av, zappy->options))
//         return 84;
//     if (!handle_options(zappy->options))
//         return 84;
//     if (!setup_zappy_content(zappy))
//         return 84;

//     create_player(zappy, 0, "martin");

//     ai_connect_nbr_request(zappy, NULL, zappy->server->clients);

//     free(zappy);
// }

Test(request_tests, request_ai_eject)
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

    create_player(zappy, 0, "martin");

    zappy->server->is_gui_connected = true;

    ai_eject_request(zappy, NULL, zappy->server->clients);

    free(zappy);
}

Test(request_tests, request_ai_move_player)
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

    create_player(zappy, 0, "martin");

    zappy->server->is_gui_connected = true;

    ai_forward_request(zappy, NULL, zappy->server->clients);
    ai_left_request(zappy, NULL, zappy->server->clients);
    ai_left_request(zappy, NULL, zappy->server->clients);
    ai_left_request(zappy, NULL, zappy->server->clients);
    ai_left_request(zappy, NULL, zappy->server->clients);
    ai_left_request(zappy, NULL, zappy->server->clients);
    ai_right_request(zappy, NULL, zappy->server->clients);
    ai_right_request(zappy, NULL, zappy->server->clients);
    ai_right_request(zappy, NULL, zappy->server->clients);
    ai_right_request(zappy, NULL, zappy->server->clients);
    ai_right_request(zappy, NULL, zappy->server->clients);

    ai_invalid_request(zappy, NULL, zappy->server->clients);

    free(zappy);
}

Test(request_tests, request_ai_look)
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

    create_player(zappy, 0, "martin");

    zappy->server->is_gui_connected = true;

    ai_look_request(zappy, NULL, zappy->server->clients);
    ai_forward_request(zappy, NULL, zappy->server->clients);
    ai_look_request(zappy, NULL, zappy->server->clients);
    ai_forward_request(zappy, NULL, zappy->server->clients);
    ai_look_request(zappy, NULL, zappy->server->clients);
    ai_forward_request(zappy, NULL, zappy->server->clients);

    free(zappy);
}

Test(request_tests, request_ai_inventory)
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

    create_player(zappy, 0, "martin");

    zappy->server->is_gui_connected = true;

    ai_inventory_request(zappy, NULL, 0);

    free(zappy);
}

Test(request_tests, request_ai_set)
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

    create_player(zappy, 0, "martin");

    get_resource_from_request("set food\n");
    get_resource_from_request("set marvin\n");
    get_resource_from_request("set marvin food\n");

    free(zappy);
}

Test(request_tests, request_ai_dead)
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

    create_player(zappy, 0, "martin");

    check_death(zappy, 0);
    zappy->client[0].player.resource_inventory[FOOD].quantity = 0;
    check_death(zappy, 0);

    free(zappy);
}

Test(request_tests, request_ai_move_around)
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

    create_player(zappy, 0, "martin");

    for (int index = 0; index < 15; index += 1)
        ai_right_request(zappy, NULL, zappy->server->clients);

    for (int index = 0; index < 15; index += 1)
        ai_left_request(zappy, NULL, zappy->server->clients);

    for (int index = 0; index < 15; index += 1)
        ai_forward_request(zappy, NULL, zappy->server->clients);

    free(zappy);
}

#include "request.h"

Test(queue_test, queue_global)
{
    list_t list = NULL;

    queue_is_empty(list);

    queue_pop_front(&list);
    queue_clear(&list);

    queue_get_size(list);

    char elem[5] = "test";
    queue_push_back(&list, &elem, sizeof(elem));
    queue_push_back(&list, &elem, sizeof(elem));
    queue_push_back(&list, &elem, sizeof(elem));

    queue_get_size(list);

    queue_get_front(list);
    queue_pop_front(&list);

    queue_clear(&list);

}
