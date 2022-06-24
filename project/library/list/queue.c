/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** list
*/

#include "listlib.h"

unsigned int queue_get_size(list_t list)
{
    unsigned int list_size = 0;

    if (list_is_empty(list))
        return 0;
    while (list) {
        list_size += 1;
        list = list->next;
    }
    return (list_size);
}

bool queue_is_empty(list_t list)
{
    return ((list == NULL) ? true : false);
}

void queue_clear(list_t *front_ptr)
{
    while (*front_ptr != NULL)
        queue_pop_front(front_ptr);

}

void *queue_get_front(list_t list)
{
    return ((list == NULL) ? NULL : list->value);
}

bool queue_push_back(list_t *front_ptr, void *elem, int type_size)
{
    list_t node = malloc(sizeof(node_t));
    list_t list = *front_ptr;

    if (!node)
        return false;
    node->value = malloc(type_size);
    if (!node->value)
        return false;
    for (int i = 0; i < type_size; i++)
        *(char *)(node->value + i) = *(char *)(elem + i);
    node->next = NULL;
    if (!list)
        *front_ptr = node;
    else {
        while (list->next)
            list = list->next;
        list->next = node;
    }
    return true;
}

bool queue_pop_front(list_t *front_ptr)
{
    list_t list = *front_ptr;

    if (!list)
        return false;
    *front_ptr = list->next;
    if (list->value)
        free(list->value);
    if (list)
        free(list);
    return true;
}
