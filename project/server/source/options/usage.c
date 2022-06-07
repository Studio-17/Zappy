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
    printf("%s\n", OPTIONS_ERROR_MESSAGES[error_code].error_message);
    printf("%s\n", USAGE_MESSAGE);
}
