/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

    #include <vector>
    #include <string>

class Map {
    public:
        Map();
        ~Map();

    protected:
    private:
        std::vector<std::vector<std::string>> _map;
};

#endif /* !MAP_HPP_ */
