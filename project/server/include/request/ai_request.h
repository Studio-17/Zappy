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
    void ai_take_request(zappy_t *zappy, void *data, int player_index);
    void ai_set_request(zappy_t *zappy, void *data, int player_index);
    void ai_incantation_request(zappy_t *zappy, void *data, int player_index);


    // Tools //
    int get_resource_from_request(char *target);
    void ai_response_ok_ko(int socket, bool status);


#endif /* !AI_REQUEST_H_ */
