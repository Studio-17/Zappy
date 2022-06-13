/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** usage
*/

#include "options/options.h"
#include "options/usage.h"

void print_usage(int error_code)
{
    if (error_code != OPTIONS_ERROR_NONE)
        printf("%s\n", options_error_messages[error_code].error_message);
    printf("%s\n", USAGE_MESSAGE);
}
