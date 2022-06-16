/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Options
*/

#ifndef OPTIONS_HPP_
#define OPTIONS_HPP_

#include <iostream>
#include <string>
#include <utility>

#include <getopt.h>

#include "Errors/ErrorsModules/Options/OptionsErrors.hpp"

class Options {
    public:
        Options();
        ~Options();

        void setupOptions(int ac, char **av);
        void handleOptions();

        void printUsage();

        int getPort() { return (_port); };
        std::string getName() { return (_name); };
        std::string getMachine() { return (_machine); };

    protected:
    private:
        int _port;
        std::string _name;
        std::string _machine = "127.0.0.1";
};

#endif /* !OPTIONS_HPP_ */
