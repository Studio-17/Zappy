/*
** EPITECH PROJECT, 2022
** project
** File description:
** ai_request
*/

#ifndef AI_REQUEST_H_
    #define AI_REQUEST_H_

    #include "server.h"

    void ai_forward_request(zappy_t *zappy, void *data, int player_index);
    void ai_right_request(zappy_t *zappy, void *data, int player_index);
    void ai_left_request(zappy_t *zappy, void *data, int player_index);

    void ai_look_request(zappy_t *zappy, void *data, int player_index);
    void ai_inventory_request(zappy_t *zappy, void *data, int player_index);
    void _ai_broadcast_text_request(zappy_t *zappy, void *data, int player_index);

    void ai_connect_nbr_request(zappy_t *zappy, void *data, int player_index);
    void ai_fork_request(zappy_t *zappy, void *data, int player_index);
    void ai_eject_request(zappy_t *zappy, void *data, int player_index);

    void ai_take_request(zappy_t *zappy, void *data, int player_index);
    void ai_set_request(zappy_t *zappy, void *data, int player_index);
    void ai_incantation_request(zappy_t *zappy, void *data, int player_index);

    void ai_invalid_request(zappy_t *zappy, void *data, int player_index);

    // Tools //
    int get_resource_from_request(char *target);
    void ai_response_ok_ko(int socket, bool status);
    void move(zappy_t *zappy, position_t movement, int player_index);
    bool check_death(zappy_t *zappy, int player_index);

#endif /* !AI_REQUEST_H_ */
