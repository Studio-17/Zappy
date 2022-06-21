/*
** EPITECH PROJECT, 2022
** project
** File description:
** Ia
*/

#ifndef IA_HPP_
#define IA_HPP_

    #include "IAClient.hpp"

class Ia {
    public:
        Ia();
        ~Ia();

        void startIa();

        void setUpOptions(int ac, char **av);
        void handleOptions();

        void mainLoop();


    protected:
    private:
        IAClient _client;
        std::string _mapSize;

        std::string _action;
};

#endif /* !IA_HPP_ */
