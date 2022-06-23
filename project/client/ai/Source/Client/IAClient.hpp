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

    class IAClient {
        public:
            IAClient();
            ~IAClient();

            void setup();
            void connection();

            void handle();

            void serverSentResponse();

            std::map<std::string, int> getInvetory() { return _inventory; };
            void setInventory(std::map<std::string, int> inventory) { _inventory = inventory; };

            std::map<std::string, int> getTimeLimit() { return _timeLimit; };
            void setTimeLimit(std::map<std::string, int> timeLimit) { _timeLimit = timeLimit; };

            void createMap(int mapHeight, int mapWidth);
            std::map<std::string, int> createTile();

            std::vector<std::vector<std::map<std::string, int>>> getContentOfMap() { return _contentOfMap; };

            void setContentTile(std::map<std::string, int> contentOfTile, int x, int y) { _contentOfMap.at(y).at(x) = contentOfTile; };
            std::map<std::string, int> getContentOfATile(int x, int y) { return _contentOfMap.at(y).at(x); };

            void PutAResourceDown(std::string resource, int x, int y) { _contentOfMap.at(y).at(x).at(resource)++; };
            void GrabAResource(std::string resource, int x, int y) { _contentOfMap.at(y).at(x).at(resource)--; };

            void setupOptions(int ac, char **av) { _options->setupOptions(ac, av); };
            void handleOptions() { _options->handleOptions(); };

            void postRequest(int socketId, std::string const &request) { dprintf(socketId, "%s\n", request.c_str()); };
            std::string getRequest(int socketId);

            std::pair<int, int> getMapSize() { return _mapSize; };
            void setMapSize(std::string str);

            int getSocket() const { return _socket; };

            std::string handleAction(std::string const &action);

        protected:
        private:
            int _socket;
            sockaddr_in _server;

            std::unique_ptr<IAOptions> _options;
            std::pair<int, int> _mapSize;
            std::map<std::string, int> _inventory;
            std::map<std::string, int> _timeLimit;
            std::vector<std::vector<std::map<std::string, int>>> _contentOfMap;
    };

#endif /* !IACLIENT_HPP_ */
