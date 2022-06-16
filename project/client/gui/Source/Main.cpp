/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Main
*/

#include "Options/Options.hpp"
#include "App.hpp"

int main(int ac, char **av)
{
    App app("MyApp", 1920, 1080);

    try {
        app.setUpOptions(ac, av);
        app.handleOptions();
        app.startApp();
    } catch (OptionsErrors const &OptionError) {
        std::cerr << OptionError.what() << std::endl;
    }

    return (0);
}
