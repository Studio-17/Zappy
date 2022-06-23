/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** App
*/

#ifndef APP_HPP_
#define APP_HPP_

    #include <iostream>
    #include <functional>
    #include <map>
    #include <unordered_map>

    #include "Window.hpp"
    #include "Camera.hpp"
    #include "Options.hpp"
    #include "Client.hpp"
    #include "Game.hpp"
    #include "IListener.hpp"
    #include "IScene.hpp"
    #include "netlib.h"

class App : public IListener {
    public:
        App(std::string const &name, int width, int height);
        ~App();

        void updateInformations(char *data, int type) override{};

        void startApp();
        void startMainLoop();

        void setupOptions(int ac, char **av);
        void handleOptions();

    protected:
    private:
        Options _options{};
        RayLib::Window _window;

        std::unordered_map<Scenes, std::shared_ptr<IScene>> _menuScenes; ///< Menu scenes
        std::shared_ptr<Client> _client;
        std::shared_ptr<RayLib::CinematicCamera> _camera;
        Scenes _activeScene;

};

#endif /* !APP_HPP_ */
