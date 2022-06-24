/*
** EPITECH PROJECT, 2022
** project
** File description:
** Ia
*/

#ifndef IA_HPP_
    #define IA_HPP_

    #include <queue>

    #include "IAClient.hpp"

class Ia {
    public:
        Ia();
        ~Ia();

        void startIa();

        void setUpOptions(int ac, char **av) { _client.setupOptions(ac, av); };
        void handleOptions() { _client.handleOptions(); };

        std::string takeObject(std::string object) { return ("Take " + transformRessourceToAction(object) + "\n"); }; // Take object
        std::string setObject(std::string object) { return ("Set " + transformRessourceToAction(object) + "\n"); }; // Set object

        std::string replaceCharacters(std::string str, const std::string& from, const std::string& to); // change all strings to another string in a string

        std::string transformRessourceToAction(std::string object); // transform a basic object to an action ex: 'food' to 'Food'
        std::vector<std::map<std::string, bool>> parseLook(std::string response); // Function to parse the look string

        bool searchGem(std::string const &gem);
        bool wantToTakeAnyObject(std::vector<std::map<std::string, bool>> objects); // Check if in the tiles there is a cool object

        int getCenteredTile(int level) { return (level * (level + 1)); }; // Get the position of the centered tile of the ia vue
        std::vector<ACTIONS> moveToTile(int tile); // tranform a tile position to a vector of movements to go to the tile and take the object

        void forward(std::string const &serverResponse);
        void turnLeft(std::string const &serverResponse);
        void turnRight(std::string const &serverResponse);
        void look(std::string const &serverResponse);
        void handleEvent(ACTIONS action, std::string const &response);
        void addActionToQueu(ACTIONS action);
        void addMessageToQueu(std::string const &serverResponse);
        void mainLoop();

    protected:
    private:
        IAClient _client; //!< IAClient
        std::string _mapSize; //!< Map size
        std::map<std::size_t, std::map<std::string, int>> _levelsToObtain; //!< Map of the levels to obtain

        int _actualLevel; //!< actual level of the ia
        std::map<std::string, int> _inventory; //!< Map of the inventory
        std::string _action; //!< Action to do

        std::pair<int, std::string> _objectToTake; //!< Object to take
        bool _isDead;

        std::queue<ACTIONS> _requestListToSend; //!< Queue of the requests to send
        std::queue<ACTIONS> _requestListSent; //!< Queue of the requests sent
        std::queue<std::string> _requestListReceived; //!< Queue of the requests received
};

#endif /* !IA_HPP_ */
