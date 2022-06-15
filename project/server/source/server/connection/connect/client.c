/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#include "minilib.h"

#include "server/server.h"

void get_request(int client_socket)
{
    char msg[24] = {0};

    bzero(msg, sizeof(msg));
    recv(client_socket, msg, sizeof(msg), 0);

    printf("[SERVER RECV] %s", msg);
}

void connect_client(server_t *server)
{
    int client_socket;
    if (FD_ISSET(server->ss->server, &server->sd->readfd))
    {
        if ((client_socket = accept(server->ss->server,
                                 (struct sockaddr *)&server->address, (socklen_t *)&server->address_length)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        send_response(server, client_socket, "WELCOME\n");
        get_request(client_socket);
        send_response(server, client_socket, strcat(my_itoa(client_socket), "\n"));
        send_response(server, client_socket, "10x10\n");

        add_client_to_server(server, client_socket);
    }
}

void clear_socket_set(server_t *server)
{
    FD_ZERO(&server->sd->readfd);
}

void add_server_socket_to_set(server_t *server)
{
    FD_SET(server->ss->server, &server->sd->readfd);
    server->sd->max_socket_descriptor = server->ss->server;
}

void add_client_socket_to_set(server_t *server)
{
    for (int index = 0; index < server->ss->max_client; index += 1)
    {
        server->sd->socket_descriptor = server->ss->client[index];

        if (server->sd->socket_descriptor > 0)
            FD_SET(server->sd->socket_descriptor, &server->sd->readfd);

        if (server->sd->socket_descriptor > server->sd->max_socket_descriptor)
            server->sd->max_socket_descriptor = server->sd->socket_descriptor;
    }
}

bool wait_for_connections(server_t *server)
{
    if ((select(server->sd->max_socket_descriptor + 1, &server->sd->readfd, NULL, NULL, NULL) < 0))
    {
        perror("select");
        return (false);
    } else {
        return (true);
    }
}

void send_response(server_t *server, int client_socket, char *message)
{
    printf("[SERVER SEND] %s", message);

    if (send(client_socket, message, strlen(message), 0) != (ssize_t)strlen(message))
    {
        perror("send");
        exit(EXIT_FAILURE);
    }
}

void add_client_to_server(server_t *server, int client_socket)
{
    for (int index = 0; index < server->ss->max_client; index += 1)
    {
        if (server->ss->client[index] == 0)
        {
            server->ss->client[index] = client_socket;
            break;
        }
    }
}
