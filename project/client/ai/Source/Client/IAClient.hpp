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

            void setupOptions(int ac, char **av);
            void handleOptions();

            void postRequest(int socketId, std::string const &request);
            std::string getRequest(int socketId);

            std::string getMapSize() const;

            int getSocket() const;

            std::string handleAction(std::string const &action);

        protected:
        private:
            int _socket;
            sockaddr_in _server;

            std::unique_ptr<IAOptions> _options;
            std::string _mapSize;
    };

#endif /* !IACLIENT_HPP_ */
