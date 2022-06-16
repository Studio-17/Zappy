/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** parser
*/

#define _GNU_SOURCE

#include "../../include/netlib.h"

static int my_atoi(char *string)
{
    int result = 0;

    for (int index = 0; string[index] != '\0'; index += 1)
    {
        if (string[index] <= '9' && string[index] >= '0')
            result = result * 10 + string[index] - '0';
        else
            continue;
    }

    if (result < 1)
        return (0);

    return (result);
}

response_payload_t get_response_payload(char *message)
{
    // "3;OK;moved" RESP

    char *token = strtok(message, ";");
    char *payload[3];

    for (int index = 0; token != NULL; index += 1) {
        asprintf(&payload[index], "%s", token);
        token = strtok(NULL, ";");
    }

    return (parse_response_payload(payload));
}

response_payload_t parse_response_payload(char **payload)
{
    response_payload_t response_payload;

    response_payload.id = my_atoi(payload[0]);
    response_payload.status = ((strcmp(payload[1], "OK") == 0) ? true : false);
    response_payload.message = payload[2];

    return (response_payload);
}

request_payload_t get_request_payload(char *message)
{
    // "1;Forward"  REQT

    char *token = strtok(message, ";");
    char *payload[2];

    for (int index = 0; token != NULL; index += 1) {
        asprintf(&payload[index], "%s", token);
        token = strtok(NULL, ";");
    }

    return (parse_request_payload(payload));
}

request_payload_t parse_request_payload(char **payload)
{
    request_payload_t request_payload;

    request_payload.id = my_atoi(payload[0]);
    request_payload.command = payload[1];

    return (request_payload);
}
