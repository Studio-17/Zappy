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
    enum class ACTIONS {
        FORWARD,
        RIGHT,
        LEFT,
        LOOK,
        INVENTORY,
        BROADCAST_TEXT,
        CONNECT_NBR,
        FORK,
        EJECT,
        TAKE_OBJECT,
        SET_OBJECT,
        INCANTATION,
    };

    enum class OBJECTS {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
        DEFAULT
    };

    public:
        Ia();
        ~Ia();

        void startIa();

        void setUpOptions(int ac, char **av);
        void handleOptions();

        std::string takeObject(OBJECTS object);
        std::string setObject(OBJECTS object);
        std::string doAction(ACTIONS action);

        std::string replaceCharacters(std::string str, const std::string& from, const std::string& to); // change all strings to another string in a string

        std::string transformObjectToAction(std::string object); // transform a basic object to an action ex: 'food' to 'Food'
        std::vector<std::vector<std::string>> parseLook(std::string response); // Function to parse the look string
        OBJECTS wantToTakeAnObject(std::string response); // Check if in the tiles there is a cool object
        std::vector<ACTIONS> moveToTile(int tile, OBJECTS object); // tranform a tile position to a vector of movements to go to the tile and take the object

        void mainLoop();


    protected:
    private:
        IAClient _client;
        std::string _mapSize;
        std::map<ACTIONS, std::string> _actionCommands;
        std::map<OBJECTS, std::string> _objectCommands;

        std::string _action;
};

#endif /* !IA_HPP_ */
