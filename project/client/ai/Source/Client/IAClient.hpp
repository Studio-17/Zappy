/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Client
*/

#ifndef IACLIENT_HPP_
    #define IACLIENT_HPP_

    #include <cstring>

    #include <memory>

    #include <netdb.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <map>
    #include <vector>
    #include<iostream>
    #include<algorithm>

    #include "Errors/ErrorsModules/Client/ClientErrors.hpp"

    #include "Options/IAOptions.hpp"

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

class IAClient {
    public:
        IAClient();
        ~IAClient();

        // Methods
        std::string getMapSize() const { return _mapSize; };
        int getSocket() const { return _socket; };
        std::map<std::string, int> getInvetory() { return _inventory; };
        void setInventory(std::map<std::string, int> inventory) { _inventory = inventory; };
        std::map<std::string, int> getTimeLimit() { return _timeLimit; };
        void setTimeLimit(std::map<std::string, int> timeLimit) { _timeLimit = timeLimit; };
        std::vector<std::map<std::string, bool>> getAllObjPerTile() const { return _allObjPerTile; };
        void setAllObjPerTile(std::vector<std::map<std::string, bool>> allObjPerTile) { _allObjPerTile = allObjPerTile; };


        // Post & Get a request from server
        void postRequest(int socketId, std::string const &request);
        std::string getRequest(int socketId);
        void serverSentResponse();


        // Setup connection IA
        void setup();
        void connection();
        void handle();
        void setupOptions(int ac, char **av);
        void handleOptions();


        std::vector<std::map<std::string, bool>> parseLook(std::string response);
        std::pair<ACTIONS, std::string> handleAction(ACTIONS action);
        void forward();
        void turnLeft();
        void turnRight();
        void look();

    protected:
    private:
        int _socket;
        sockaddr_in _server;
        std::unique_ptr<IAOptions> _options;
        std::string _mapSize;

        std::map<std::string, int> _inventory;
        std::map<std::string, int> _timeLimit;
        std::map<ACTIONS, std::string> _actionCommands; //!< Map of the action commands

        std::vector<std::map<std::string, bool>> _allObjPerTile;
};

#endif /* !IACLIENT_HPP_ */
