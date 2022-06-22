/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<Client> client) : AScene()
{
    _client = client;
    _client->setup();
    _client->connection();
}

MainMenu::MainMenu() : AScene()
{
}

MainMenu::~MainMenu()
{
}
