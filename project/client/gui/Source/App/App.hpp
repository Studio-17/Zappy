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
    #include "Map.hpp"

class App {
    public:
        App(std::string const &name, int width, int height);
        ~App();

        void startApp();
        void startConnection();
        void startMainLoop();

        void setUpOptions(int ac, char **av);
        void handleOptions();

    protected:
    private:
        Options _options;
        RayLib::Window _window;
        RayLib::CinematicCamera _camera;
        Map _gameMap;
};

#endif /* !APP_HPP_ */
