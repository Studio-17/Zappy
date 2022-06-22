/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** queue
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct node_s {
    void *value;
    struct node_s *next;
} node_t;

typedef node_t *list_t;

unsigned int list_get_size(list_t list);
bool list_is_empty(list_t list);
typedef void (*value_displayer_t)(const void *value);
void list_dump(list_t list, value_displayer_t val_disp);

bool list_add_elem_at_front(list_t *front_ptr, void *elem);
bool list_add_elem_at_back(list_t *front_ptr, void *elem);
bool list_add_elem_at_position(list_t *front_ptr, void *elem, unsigned int position);

bool list_del_elem_at_front(list_t *front_ptr);
bool list_del_elem_at_back(list_t *front_ptr);
bool list_del_elem_at_position(list_t *front_ptr, unsigned int position);

void list_clear(list_t *front_ptr);

void *list_get_elem_at_front(list_t list);
void *list_get_elem_at_back(list_t list);
void *list_get_elem_at_position(list_t list, unsigned int position);

unsigned int list_get_size(list_t list)
{
    unsigned int list_size = 0;

    if (list_is_empty(list))
    {
        return (0);
    }
    while (list)
    {
        list_size += 1;
        list = list->next;
    }
    return (list_size);
}

bool list_is_empty(list_t list)
{
    return ((list == NULL) ? true : false);
}

void list_dump(list_t list, value_displayer_t val_disp)
{
    if (list_is_empty(list))
    {
        return;
    }
    while (list)
    {
        (*val_disp)(list->value);
        list = list->next;
    }
    return;
}

void list_clear(list_t *front_ptr)
{
    while (*front_ptr != NULL)
    {
        list_del_elem_at_front(front_ptr);
    }
    return;
}

void *list_get_elem_at_front(list_t list)
{
    return ((list == NULL) ? 0 : list->value);
}

void *list_get_elem_at_back(list_t list)
{
    if (list == NULL)
    {
        return (0);
    }
    else
    {
        while (list->next != NULL)
            list = list->next;
        return (list->value);
    }
}

void *list_get_elem_at_position(list_t list, unsigned int position)
{
    if (position == 0)
    {
        return (list_get_elem_at_front(list));
    }
    if (list_get_size(list) <= position)
    {
        return (false);
    }
    while (position--)
    {
        if (list == NULL)
        {
            return (0);
        }
        list = list->next;
    }
    return (list->value);
}

bool list_add_elem_at_front(list_t *front_ptr, void *elem)
{
    list_t node = malloc(sizeof(list_t));

    if (front_ptr == NULL)
        *front_ptr = node;
    node->value = elem;
    node->next = (*front_ptr);
    (*front_ptr) = node;
    return (true);
}

bool list_add_elem_at_back(list_t *front_ptr, void *elem)
{
    list_t node = malloc(sizeof(list_t));
    list_t list = *front_ptr;

    if (node == NULL)
    {
        return (false);
    }
    if (list == NULL)
    {
        *front_ptr = node;
    }
    else
    {
        while (list->next)
            list = list->next;
        list->next = node;
    }
    node->value = elem;
    node->next = NULL;
    return (true);
}

bool list_add_elem_at_position(list_t *front_ptr, void *elem, unsigned int p)
{
    list_t node = malloc(sizeof(list_t));
    list_t list = *front_ptr;

    if (node == NULL)
        return (false);
    if (p == 0)
        return (list_add_elem_at_front(front_ptr, elem));
    if (list_get_size(list) < p)
        return (false);
    node->value = elem;
    node->next = NULL;
    while (list && --p)
    {
        if (list == NULL)
            return (false);
        list = list->next;
    }
    node->next = list->next;
    list->next = node;
    return (true);
}

bool list_del_elem_at_front(list_t *front_ptr)
{
    list_t list = *front_ptr;

    if (list == NULL)
    {
        return (false);
    }
    (*front_ptr) = (*front_ptr)->next;
    list->next = NULL;
    if (list != NULL)
    {
        free(list);
    }
    return (true);
}

bool list_del_elem_at_back(list_t *front_ptr)
{
    list_t list = *front_ptr;

    if (!list)
    {
        return (false);
    }
    while (list->next && list->next->next)
        list = list->next;
    if (!list->next)
    {
        *front_ptr = NULL;
    }
    else
    {
        free(list->next);
        list->next = NULL;
    }
    return (true);
}

bool list_del_elem_at_position(list_t *front_ptr, unsigned int position)
{
    unsigned int count = 1;
    list_t list = *front_ptr;

    if (*front_ptr == NULL)
    {
        return (0);
    }
    if (list_get_size(*front_ptr) <= position)
    {
        return (0);
    }
    if (position == 0)
    {
        return (list_del_elem_at_front(front_ptr));
    }
    while (count < position)
    {
        list = list->next;
        count += 1;
    }
    list->next = list->next->next;
    return (true);
}


// BEGIN


typedef void (*request_handler)(void *, void *, int);

void ai_forward_request(void *structure, void *data, int index)
{
    write(1, "ok\n", 4);
}

void ai_right_request(void *structure, void *data, int index)
{
    write(1, "ok\n", 4);
}

void ai_left_request(void *structure, void *data, int index)
{
    write(1, "ok\n", 4);
}

void ai_look_request(void *structure, void *data, int index)
{
    write(1, "[tile1, tile2, ...]\n", 21);
}

void ai_inventory_request(void *structure, void *data, int index)
{
    write(1, "[food 10, linemate 2, deraumere 1, sibur 0, mendiane 1, phiras 1, thystame 1]\n", 79);
}

void ai_incantation_request(void *structure, void *data, int index)
{
    write(1, "Elevation underway\nCurrent level: k\n", 37);
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
        .time = 7,
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

int execute_tasks(list_t list)
{
    while (list_get_size(list) != 0)
    {
        data_t *request = malloc(sizeof(data_t));
        request = list_get_elem_at_front(list);

        clock_t end = clock();
        unsigned long millis = (end - request->clock) * 1000 / CLOCKS_PER_SEC;

        if (millis >= (request->request_time * 1000)) {

            request->request(NULL, NULL, 0);
            printf("time spent: %ld (expected %d)\n", millis / 1000, request->request_time);

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

        size_t bufsize = 32;
        char *buffer = (char *)malloc(bufsize * sizeof(char));
        if (buffer == NULL) {
            perror("malloc");
            exit(1);
        }

        __attribute((unused)) int status = getline(&buffer, &bufsize, stdin);

        int saved_index = -1;
        for (int index = 0; index < 5; index += 1) {
            if (strcmp(buffer, request_table[index].request) == 0) {

                saved_index = index;
                break;

            }
        }

        bool error_status = true;

        if (saved_index == -1) {
            write(1, "ko\n", 4);
            free(buffer);
            error_status = false;
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

            list_add_elem_at_back(&list, &new_data);
        }

        if (error_status)
            execute_tasks(list);

    }

    return (0);
}
