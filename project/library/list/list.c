/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** list
*/

#include "listlib.h"

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
