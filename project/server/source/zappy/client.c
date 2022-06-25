/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#include "server.h"
#include "request.h"

void free_clients(ai_client_t *clients, int max_clients)
{
    for (int index = 0; index != max_clients; index++) {
        free(clients[index].player.resource_inventory);
        list_t tmp_ptr = clients[index].list;
        while (tmp_ptr) {
            free((*(data_t *)tmp_ptr->value).request.data);
            tmp_ptr = tmp_ptr->next;
        }
        queue_clear(&clients[index].list);
    }
    free(clients);
}