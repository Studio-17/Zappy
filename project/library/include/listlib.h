/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** listlib
*/

#ifndef LISTLIB_H_
    #define LISTLIB_H_

    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>

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

#endif /* !LISTLIB_H_ */
