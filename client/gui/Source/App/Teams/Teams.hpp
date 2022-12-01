/*
** EPITECH PROJECT, 2022
** project
** File description:
** Teams
*/

#ifndef TEAMS_HPP_
#define TEAMS_HPP_

    #include "Player.hpp"

class Teams {
    public:
        Teams();
        ~Teams();

    protected:
    private:
        std::vector<std::shared_ptr<Object::Player>> _players;
};

#endif /* !TEAMS_HPP_ */
