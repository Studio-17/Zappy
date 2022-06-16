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

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Errors/ErrorsModules/Client/ClientErrors.hpp"

#include "Options/Options.hpp"

class Client {
    public:
        Client(Options const &options);
        ~Client();

        void setup();
        void connection();

        void handle();

    protected:
    private:
        int _socket;
        sockaddr_in _server;

        std::unique_ptr<Options> _options;
};

#endif /* !CLIENT_HPP_ */
