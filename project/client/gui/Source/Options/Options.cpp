/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Options
*/

#include "Options.hpp"

Options::Options()
{

}

Options::~Options()
{
}

void Options::setupOptions(int ac, char **av)
{
    int opt = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'e'},
        {"port", required_argument, 0, 'p'},
        {"machine", required_argument, 0, 'h'},
        {0, 0, 0, 0}};

    int long_index = 0;
    while ((opt = getopt_long(ac, av, "ep:h:",
                              long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'e':
            printUsage();
            break;
        case 'p':
            _port = std::stoi(optarg);
            break;
        case 'h':
            _machine = std::string(optarg);
            break;
        default:
            printUsage();
            break;
        }
    }
}

void Options::handleOptions()
{
    if (_port < 1 || _machine.empty())
        throw OptionsErrors("Invalid options");
}

void Options::printUsage()
{
    std::cout << "  ./zappy_gui --help" << std::endl;
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
    std::cout << "      port is the port number" << std::endl;
    std::cout << "      machine is the name of the machine; localhost by default" << std::endl;

    exit(0);
}
