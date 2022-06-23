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

    public:
        Ia();
        ~Ia();

        void startIa();

        void setUpOptions(int ac, char **av) { _client.setupOptions(ac, av); };
        void handleOptions() { _client.handleOptions(); };

        std::string takeObject(std::string object) { return ("Take " + transformRessourceToAction(object) + "\n"); }; // Take object
        std::string setObject(std::string object) { return ("Set " + transformRessourceToAction(object) + "\n"); }; // Set object
        std::string doAction(ACTIONS action) { return (_actionCommands.at(action)); };

        std::string replaceCharacters(std::string str, const std::string& from, const std::string& to); // change all strings to another string in a string

        std::string transformRessourceToAction(std::string object); // transform a basic object to an action ex: 'food' to 'Food'
        std::vector<std::map<std::string, bool>> parseLook(std::string response); // Function to parse the look string

        bool searchGem(std::string const &gem);
        bool wantToTakeAnyObject(std::vector<std::map<std::string, bool>> objects); // Check if in the tiles there is a cool object

        int getCenteredTile(int level) { return (level * (level + 1)); }; // Get the position of the centered tile of the ia vue
        std::vector<ACTIONS> moveToTile(int tile); // tranform a tile position to a vector of movements to go to the tile and take the object

        void mainLoop();




    protected:
    private:
        IAClient _client; //!< IAClient
        std::string _mapSize; //!< Map size
        std::map<ACTIONS, std::string> _actionCommands; //!< Map of the action commands
        std::map<std::size_t, std::map<std::string, int>> _levelsToObtain; //!< Map of the levels to obtain

        int _actualLevel; //!< actual level of the ia
        std::map<std::string, int> _inventory; //!< Map of the inventory
        std::string _action; //!< Action to do

        std::pair<int, std::string> _objectToTake; //!< Object to take
};

#endif /* !IA_HPP_ */
