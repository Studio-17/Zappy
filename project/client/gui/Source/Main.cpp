/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Main
*/

#include "Options/Options.hpp"

int main(int ac, char **av)
{
    Options options;

    try {
        options.setupOptions(ac, av);
        options.handleOptions();
    } catch (OptionsErrors const &OptionError) {
        std::cerr << OptionError.what() << std::endl;
    }

    return (0);
}
