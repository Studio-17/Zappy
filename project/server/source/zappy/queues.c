/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** queue
*/

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include <unistd.h>


// BEGIN


typedef void (*request_handler)(void *, void *, int);

void ai_forward_request(void *structure, void *data, int index)
{
    printf("Moove\n");
}

void ai_right_request(void *structure, void *data, int index)
{
    printf("ok\n");
}

void ai_left_request(void *structure, void *data, int index)
{
    printf("ok\n");
}

void ai_look_request(void *structure, void *data, int index)
{
    printf("[tile1, tile2, ...]\n");
}

void ai_inventory_request(void *structure, void *data, int index)
{
    printf("[food 10, linemate 2, deraumere 1, sibur 0, mendiane 1, phiras 1, thystame 1]\n");
}

void ai_incantation_request(void *structure, void *data, int index)
{
    printf("Elevation underway\nCurrent level: k\n");
}

typedef struct ai_request_s {
    char *request;
    request_handler handler;
    int time;
} ai_request_t;

static const ai_request_t request_table[] = {
    {
        .request = "Forward\n",
        .handler = &ai_forward_request,
        .time = 1,
    },
    {
        .request = "Right\n",
        .handler = &ai_right_request,
        .time = 7,
    },
    {
        .request = "Left\n",
        .handler = &ai_left_request,
        .time = 7,
    },
    {
        .request = "Look\n",
        .handler = &ai_look_request,
        .time = 7,
    },
    {
        .request = "Inventory\n",
        .handler = &ai_inventory_request,
        .time = 1,
    },
    {
        .request = "Incantation\n",
        .handler = &ai_incantation_request,
        .time = 30,
    },
};

typedef struct argument_handler_s {
    void *structure;
    void *data;
    int index;
} argument_handler_t;

typedef struct data_s {
    request_handler request;
    argument_handler_t arguments;

    int request_time;
    clock_t clock;
} data_t;

#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "listlib.h"

int execute_tasks(list_t *list)
{
    while (list_get_size(*list) != 0) {
        data_t request = *(data_t *)queue_get_front(*list);
        clock_t end = clock();
        unsigned long millis = (end - request.clock) * 1000 / CLOCKS_PER_SEC;
        if (millis >= (request.request_time * 1000)) {
            request.request(request.arguments.structure, request.arguments.data, request.arguments.index);
            printf("time spent: %ld (expected %d)\n", millis / 1000, request.request_time);
            queue_pop_front(list);
        }
    }
}

int main(void)
{
    list_t list = NULL;
    size_t bufsize = 32;
    char *buffer = NULL;

    while (1) {
        if (getline(&buffer, &bufsize, stdin) == -1)
            break;
        int saved_index = -1;
        for (int index = 0; index < 5; index += 1)
            if (strcmp(buffer, request_table[index].request) == 0) {
                saved_index = index;
                break;
            }
        if (saved_index == -1) {
            printf("ko\n");
        } else {
            data_t new_data = {
                .request = request_table[saved_index].handler,
                .request_time = request_table[saved_index].time,
                .arguments = {
                    .data = NULL,
                    .structure = NULL,
                    .index = 1,
                },
                .clock = clock(),
            };
            queue_push_back(&list, &new_data, sizeof(data_t));

        }
        execute_tasks(&list);
    }
    queue_clear(&list);
    free(buffer);
    return (0);
}
