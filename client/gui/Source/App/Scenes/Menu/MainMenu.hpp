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
    #include "Button.hpp"
    #include "Image.hpp"

class MainMenu : public AScene {
    public:
        MainMenu(std::shared_ptr<Client> client, std::function<void(void)> callBack);
        MainMenu();
        ~MainMenu();

        void startGame();
        void startOptions();
        void exit();

        Scenes handleEvent() override;
        void draw() override;

        void updateInformations(char *data, int type);
        void exitGame();

        void drawTextInputIp();
        void handleEventTextInputIp();

        void drawTextInputPort();
        void handleEventTextInputPort();

    protected:
    private:
        std::shared_ptr<Client> _client;

        bool _isConnected;
        bool _shouldPrintConnectionFailed = false;
        std::function<void(void)> _callBack;

        char name[19 + 1] = "\0";
        int letterCount = 0;
        Rectangle textBox = { 1920.0f / 2 - 100, 180, 300, 50 };
        bool mouseOnText = false;
        int framesCounter = 0;

        char namePort[19 + 1] = "\0";
        int letterCountPort = 0;
        Rectangle textBoxPort = { 1920.0f / 2 - 100, 280, 300, 50 };
        bool mouseOnTextPort = false;
        int framesCounterPort = 0;

        std::string _currentMachine;
        std::string _currentPort;

};

#endif /* !MAINMENU_HPP_ */
