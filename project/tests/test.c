/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>

void redirect_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(server_test, dummy, .init = redirect_std)
{
    cr_assert(true);
}
