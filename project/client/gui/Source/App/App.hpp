/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** App
*/

#ifndef APP_HPP_
#define APP_HPP_

    #include <iostream>
    #include "Window.hpp"
    #include "Camera.hpp"
    #include "Options.hpp"
    #include "Client.hpp"
    #include "Game.hpp"
    #include "IListener.hpp"

enum COMMANDS_GUI {
    MAP_SIZE,
    CONTENT_TILE,
    CONTENT_MAP,
    NAME_OF_TEAMS,
    PLAYER_POSITION,
    PLAYER_LEVEL,
    PLAYER_INVENTORY,
    TIME_UNIT,
    TIME_UNIT_MODIFICATION,
    NB_COMMANDS_GUI,
};

class App : public IListener {
    public:
        App(std::string const &name, int width, int height);
        ~App();

        void updateInformations(char *data, int type) override;

        void startApp();
        void startConnection();
        void startMainLoop();

        void setupOptions(int ac, char **av);
        void handleOptions();

        void draw();

        void handleAddPlayer(char *data);
        void handlePlayerPosition(char *data);

    protected:
    private:
        Client _client;
        Options _options{};
        RayLib::Window _window;
        RayLib::CinematicCamera _camera;
        Game _game;

        int _mapHeight = 10;
        int _mapWidth = 10;
};

#endif /* !APP_HPP_ */
