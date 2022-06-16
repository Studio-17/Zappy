/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Main
*/

#include <csignal>

#include "Client/Client.hpp"
#include "Options/Options.hpp"

void sigint_handler([[maybe_unused]] int signal_num)
{
    std::cout << "Host disconnected" << std::endl;
    std::cout << "The interrupt signal is (" << signal_num << "). \n";

    exit(0);
}

int main(int ac, char **av)
{
    signal(SIGINT, sigint_handler);

    Options options;

    try {
        options.setupOptions(ac, av);
        options.handleOptions();
    } catch (OptionsErrors const &OptionError) {
        std::cerr << OptionError.what() << std::endl;
    }

    Client client(options);

    try {
        client.setup();
        client.connection();
    } catch (ClientErrors const &ClientError) {
        std::cerr << ClientError.what() << std::endl;
    }

    return (0);
}
