/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** ai
*/

#include "server.h"
#include "request.h"
#include "ai_request.h"


void ai_base_request(zappy_t *zappy, __attribute__((unused)) void *data, __attribute__((unused))int player_index)
{
    int socket = zappy->client[player_index].socket;

    write(socket, "UNUSED REQUEST\n", strlen("UNUSED REQUEST\n"));
}

static const ai_request_t ai_request_to_handle[] = {
    {
        .request = "Forward\n",
        .command = FORWARD,
        .handler = &ai_forward_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Right\n",
        .command = RIGHT,
        .handler = &ai_right_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Left\n",
        .command = LEFT,
        .handler = &ai_left_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Look\n",
        .command = LOOK,
        .handler = &ai_look_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Inventory\n",
        .command = INVENTORY,
        .handler = &ai_inventory_request,
        .time_limit = 1,
        .data = NULL,
    },
    {
        .request = "Broadcast text\n",
        .command = BROADCAST_TEXT,
        .handler = &ai_base_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Connect_nbr\n",
        .command = CONNECT_NBR,
        .handler = &ai_connect_nbr_request,
        .time_limit = 0,
        .data = NULL,
    },
    {
        .request = "Fork\n",
        .command = FORK,
        .handler = &ai_fork_request,
        .time_limit = 42,
        .data = NULL,
    },
    {
        .request = "Eject\n",
        .command = EJECT,
        .handler = &ai_eject_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Take\n",
        .command = TAKE_OBJECT,
        .handler = &ai_take_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Set\n",
        .command = SET_OBJECT,
        .handler = &ai_set_request,
        .time_limit = 7,
        .data = NULL,
    },
    {
        .request = "Incantation\n",
        .command = INCANTATION,
        .handler = &ai_incantation_request,
        .time_limit = 300,
        .data = NULL,
    },
    {
        .request = "\n",
        .command = INVALID,
        .handler = &ai_invalid_request,
        .time_limit = 0,
        .data = NULL,
    }
};

static char *remove_elem(char *str, int index)
{
    int len = strlen(str) - index - 1;
    char *new_str = malloc(sizeof(char) * len + 1);

    if (!new_str)
        return NULL;
    for (int i = index + 1; str[i] != '\0'; i++)
        new_str[i - index - 1] = str[i];
    new_str[len] = '\0';
    free(str);
    str = strdup(new_str);
    free(new_str);
    return str;
}

static int find_elem(char const *str, char elem)
{
    int index = 0;

    while (str[index] != '\0') {
        if (str[index] == elem)
            return index;
        index++;
    }
    return -1;
}

static char *send_to_buffer(zappy_t *zappy, int player_index, char *request_data)
{
    int index = 0;
    char *text = NULL;

    if (!zappy->client[player_index].buffer)
        zappy->client[player_index].buffer = strdup(request_data);
    else {
        zappy->client[player_index].buffer = realloc(zappy->client[player_index].buffer, strlen(zappy->client[player_index].buffer) + strlen(request_data) + 2);
        strcat(zappy->client[player_index].buffer, request_data);
    }
    index = find_elem(zappy->client[player_index].buffer, '\n');
    if (index == -1)
        return NULL;
    text = strndup(zappy->client[player_index].buffer, index + 1);
    zappy->client[player_index].buffer = remove_elem(zappy->client[player_index].buffer, index);

    return text;
}

static bool is_valid_object(char *request)
{
    char *object_table[] = {
        "food",
        "linemate",
        "deraumere",
        "sibur",
        "mendiane",
        "phiras",
        "thystame",
        NULL,
    };

    for (int index = 0; object_table[index]; index += 1) {
        if (strstr(request, object_table[index]) != NULL)
            return (true);
    }

    return (false);
}

static ai_request_t push_handler(char *request, enum COMMANDS_AI type)
{
    ai_request_t tmp;

    tmp = ai_request_to_handle[type];
    tmp.data = strdup(request);
    free(request);
    return tmp;
}

ai_request_t ai_handle_request(zappy_t *zappy, int player_index)
{
    char *request_data = read_in_socket(zappy->client[player_index].socket);
    char *request = NULL;
    ai_request_t none_request = { .command = EMPTY };
    ai_request_t error_request = { .command = ERROR };
    ai_request_t out_of_range_request = { .command = OUT_OF_RANGE };

    if (!request_data)
        return (error_request);
    request = send_to_buffer(zappy, player_index, request_data);
    free(request_data);
    if (!request)
        return none_request;
    if (queue_get_size(zappy->client[player_index].list) >= 10) {
        printf("out of range\n");
        free(request);
        return (out_of_range_request);
    }

    for (int index = 0; index < NB_COMMANDS_AI; index += 1) {

        if (strncmp(request, "Set ", 4) == 0) {
            if (is_valid_object(request)) {
                return (push_handler(request, SET_OBJECT));
            }
        } else if (strncmp(request, "Take ", 5) == 0) {
            if (is_valid_object(request)) {
                return (push_handler(request, TAKE_OBJECT));
            }
        } else if (strncmp(request, ai_request_to_handle[index].request, strlen(ai_request_to_handle[index].request)) == 0) {
            return (push_handler(request, index));
        }
    }

    return (ai_request_to_handle[INVALID]);
}
