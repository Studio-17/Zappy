/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** queue
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "listlib.h"

typedef struct data_s
{
    char *request;
    int time;
    clock_t clock;
} data_t;

#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int execute_tasks(list_t list)
{
    while (list_get_size(list) != 0)
    {
        data_t *request = malloc(sizeof(data_t));
        request = list_get_elem_at_front(list);

        clock_t end = clock();
        unsigned long millis = (end - request->clock) * 1000 / CLOCKS_PER_SEC;

        if (millis >= (request->time * 1000)) {

            printf("done: %s", request->request);
            printf("time spent: %ld (expected %d)\n", millis / 1000, request->time);

            list_del_elem_at_front(&list);
        }
    }
}

int main(void)
{
    list_t list = NULL;
    srand(time(0));

    while (1)
    {

        char *buffer;
        size_t bufsize = 32;
        buffer = (char *)malloc(bufsize * sizeof(char));
        if (buffer == NULL)
        {
            perror("malloc");
            exit(1);
        }

        __attribute((unused)) int status = getline(&buffer, &bufsize, stdin);

        data_t new_data = {
            .request = buffer,
            .time = rand() % 5,
            .clock = clock(),
        };

        list_add_elem_at_back(&list, &new_data);

        execute_tasks(list);
    }

    return (0);
}
