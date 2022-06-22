/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

    #include "AScene.hpp"
    #include "Client.hpp"

class MainMenu : public AScene {
    public:
        MainMenu(std::shared_ptr<Client> client);
        MainMenu();
        ~MainMenu();

        Scenes handleEvent() override {};
        void draw() override {};

    protected:
    private:
        std::shared_ptr<Client> _client;
        bool _isConnected;
};

#endif /* !MAINMENU_HPP_ */
