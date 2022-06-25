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
    #include <iostream>
    #include <algorithm>

    #include "Errors/ErrorsModules/Client/ClientErrors.hpp"

    #include "Options/IAOptions.hpp"

enum class ACTIONS {
    NONE,
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
        std::pair<int, int> getMapSize() { return _mapSize; };
        void setMapSize(std::string str);
        int getSocket() const { return _socket; };
        std::map<std::string, int> getInvetory() { return _inventory; };


        // Post & Get a request from server
        void postRequest(int socketId, std::string const &request);
        void postRequest(int socketId, ACTIONS request);
        std::string getRequest(int socketId);
        void serverSentResponse();

        // Setup connection IA
        void setup();
        void connection();
        void handle();

        void setupOptions(int ac, char **av);
        void handleOptions();
        // void handleAction(ACTIONS action);

    protected:
    private:
        int _socket;
        sockaddr_in _server;
        std::unique_ptr<IAOptions> _options;
        std::pair<int, int> _mapSize; //!< Map size

        std::map<std::string, int> _inventory;
        // std::map<std::string, int> _timeLimit;
        std::map<ACTIONS, std::string> _actionCommands; //!< Map of the action commands
};

#endif /* !IACLIENT_HPP_ */
