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
    #include <queue>

class Ia {
    enum class DIRECTION {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
    };

    public:
        Ia();
        ~Ia();

        void startIa();

        void setUpOptions(int ac, char **av) { _client.setupOptions(ac, av); };
        void handleOptions() { _client.handleOptions(); };

        void take(std::string const &serverResponse, std::string resource);
        void set(std::string const &serverResponse, std::string resource);

        std::string replaceCharacters(std::string str, const std::string& from, const std::string& to); //!< change all strings to another string in a string

        std::string transformRessourceToAction(std::string object); //!< Transform ressource to action

        void parseLook(std::string response); //!< Function to parse the look string
        void parseInventory(std::string response); //!< Function to parse the inventory string
        void parseTake(std::string const &resource); //!< Function to parse the take string
        void parseSet(std::string const &resource);  //!< Function to parse the set string
        void clearTheInventory(); //!< Function to clear the inventory

        void fillInTheMap(std::vector<std::vector<std::string>> content, std::pair<int, int> playerPosition, DIRECTION direction); //!< Fill the map with the content of the look
        void fillInTheInventory(std::map<std::string, int> content); //!< Fill the inventory with the content of the inventory

        std::string getNeededItem(); // Function to store object to take in tile
        bool wantToTakeAnyObject(); //!< Function to see if you want to take an object in a tile

        void createMap(int mapHeight, int mapWidth); //!< Create the map of the game
        std::map<std::string, bool> createTile(); //!< Create a tile of the map

        void setContentTile(std::vector<std::string> contentOfTile, int x, int y); //!< Set the content of a tile
        void clearContentTile(int x, int y); //!< Clear the content of a tile
        std::map<std::string, bool> getContentOfATile(int x, int y) { return _contentOfMap.at(y).at(x); }; //!< Get the content of a tile

        void PutAResourceDown(std::string resource, int x, int y) { _contentOfMap.at(y).at(x).at(resource) = true; }; //!< Put a resource down in the map
        void GrabAResource(std::string resource, int x, int y) { _contentOfMap.at(y).at(x).at(resource) = false; }; //!< Grab a resource in the map

        std::pair<int, int> movePlayer(std::pair<int, int> iaPosition); //!< Move the player only forward
        void changeDirection(DIRECTION direction); //!< Change the direction of the player


        bool parseReceiveResponse(std::string message); //!< Parse the response of the server
        void forward(std::string const &serverResponse); //!< Move the player forward
        void turnLeft(std::string const &serverResponse); //!< Turn the player left
        void turnRight(std::string const &serverResponse); //!< Turn the player right
        void look(std::string const &serverResponse); //!< Set some map infos from the look response
        void inventory(std::string const &serverResponse); //!< Set the inventory from the inventory response
        void handleEvent(ACTIONS action, std::string const &response); //!< Handle the response of the server
        void addActionToQueue(ACTIONS action); //!< Add an action to the queue
        void addMessageToQueue(std::string const &serverResponse); //!< Add a message to the queue
        void sendResquestServer(); //!< Send request from queue to server
        void analyzeResponseServer(); //!< Analyze response from server
        void mainLoop(); //!< Main loop of the IA
        bool haveElementInInventory(std::string &element); //!< Check if the element is in the inventory

        bool isElementInMap(std::string const &element); //!< Check if the element is in the map
        void goToTile(int x, int y);                     //!< Go to a tile
        void searchElement();  //!< Search an element in the map
        void emptyTileAndSetGoodElement(int x, int y);
        void startIncantation();
        bool isTileEmpty(int x, int y);
        bool isElementInTile(int x, int y, std::string element);

    protected:
    private:
        IAClient _client;                      //!< IAClient
        std::pair<int, int> _actualIaPosition; //!< Actual Ia Position
        DIRECTION _actualIaDirection;          //!< Actual Ia Direction
        std::map<DIRECTION, std::pair<int, int>> _rowDirections;
        std::map<DIRECTION, std::pair<int, int>> _possibleDirections;      //!< Possible directions of the ia
        std::map<ACTIONS, std::string> _actionCommands;                    //!< Map of the action commands
        std::map<std::size_t, std::map<std::string, int>> _levelsToObtain; //!< Map of the levels to obtain

        int _actualLevel;                      //!< actual level of the ia
        std::map<std::string, int> _inventory; //!< Inventory of the ia
        std::string _action;                   //!< Action to do

        std::string _objectToTake; //!< Object to take
        bool _isDead;              //!< bool to know if the ia dead

        bool _stop;

        std::map<std::string, ACTIONS> _takeMap; //!< Map of the take commands
        std::map<std::string, ACTIONS> _setMap; //!< Map of the set commands

        std::queue<ACTIONS> _requestTmp;              //!< Queue of request store before pushing them into _requestListToSend
        std::queue<ACTIONS> _requestListToSend;       //!< Queue of the requests to send
        std::queue<ACTIONS> _requestListSent;         //!< Queue of the requests sent
        std::queue<std::string> _requestListReceived; //!< Queue of the requests received

        std::pair<int, int> _mapSize;                                        //!< Map size
        std::vector<std::vector<std::map<std::string, bool>>> _contentOfMap; //!< Content of the map

        std::string _bufferServerResponse; //!< Store all server responses before analysing them

        std::pair<int, int> _currentTileToGo; //!< Current tile to go

        std::vector<std::string> _stringElementInMap;
};

#endif /* !IA_HPP_ */
