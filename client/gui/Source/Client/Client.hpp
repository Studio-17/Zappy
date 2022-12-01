/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <cstring>

#include <memory>
#include <utility>

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Errors/ErrorsModules/Client/ClientErrors.hpp"

#include "Options/Options.hpp"
#include "EventsHandler.hpp"


class Client {
    public:
        Client();
        ~Client();

        void setup();
        void connection();

        void handle();

        void serverSentResponse();

        void setupOptions(int ac, char **av);
        void handleOptions();

        void postRequest(int socketId, std::string const &request);
        std::string getRequest(int socketId);

        void listen();

        std::pair<int, int> getMapDimension();
        EventsHandler _eventsHandler;

        bool checkConnection();


        std::string getMachine() const { return _options->getMachine(); };
        int getPort() const { return _options->getPort(); };

        void setMachine(std::string &machine);
        void setPort(int port);

    protected:
    private:
        int _socket;
        sockaddr_in _server;

        std::unique_ptr<Options> _options;
        int _clientNumber;
        std::string _mapDimension;
        bool _isConnected = false;
};

#endif /* !CLIENT_HPP_ */
