/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Main
*/

#include <csignal>

#include "Ia.hpp"
#include "Client/Client.hpp"

void sigint_handler([[maybe_unused]] int signal_num)
{
    std::cout << "Host disconnected" << std::endl;
    std::cout << "The interrupt signal is (" << signal_num << "). \n";

    exit(0);
}

int main(int ac, char **av)
{
    signal(SIGINT, sigint_handler);

    Ia IaApp(2);

    try {
        IaApp.setUpOptions(ac, av);
        IaApp.handleOptions();
        IaApp.startIa();
    } catch (OptionsErrors const &OptionError) {
        std::cerr << OptionError.what() << std::endl;
    }
    return (0);
}
