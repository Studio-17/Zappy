/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** MainMenu
*/

#include "MainMenu.hpp"
#include "Position.hpp"

MainMenu::MainMenu(std::shared_ptr<Client> client, std::function<void(void)> callBack) : AScene()
{
    _client = client;
    std::cout << "MainMenu ctor" << std::endl;
    _client->setup();

    _buttons.push_back(std::make_unique<Object::Button>("Resources/Buttons/button2.png", 3, std::bind(&MainMenu::startGame, this), Position(300, 500, 0)));
    _buttons.push_back(std::make_unique<Object::Button>("Resources/Buttons/button2.png", 3, std::bind(&MainMenu::exitGame, this), Position(300, 700, 0)));

    _images.push_back(std::make_unique<Object::Image>("Resources/Images/parallax_background.png"));

    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Connexion failed", Position(400, 650, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Start a game", Position(600, 550, 0)));
    _texts.push_back(std::make_unique<Object::Text>("Resources/Fonts/Square.ttf", "Exit", Position(600, 750, 0)));

    _texts.at(0)->setColor(RED);
    _texts.at(1)->setColor(WHITE);
    _texts.at(2)->setColor(WHITE);

    _callBack = callBack;

    SetTargetFPS(10);


}

MainMenu::MainMenu() : AScene()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::exitGame()
{
    _nextScene = Scenes::QUIT;
}

void MainMenu::startGame()
{
    if (_client->checkConnection()) {
        std::cout << "check connection" << std::endl;
        _client->handle();
        _callBack();
        _nextScene = Scenes::GAME;
    }
    else
        _shouldPrintConnectionFailed = true;
}

void MainMenu::updateInformations(char *data, int type)
{
}

void MainMenu::drawTextInputIp()
{
    DrawText("Enter IP: ", (int)textBox.x + 50, (int)textBox.y - 30, 20, DARKGRAY);
    DrawText("Current IP: ", (int)textBox.x + 350, (int)textBox.y, 20, DARKGRAY);
    DrawText(_client->getMachine().c_str(), (int)textBox.x + 500, (int)textBox.y, 20, DARKGRAY);


    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
    DrawText(TextFormat("%i/%i", letterCount, 20), 1920 / 2 - 400, 190, 20, DARKGRAY);
    if (mouseOnText)
    {
        if (letterCount < 20)
        {
            if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
        }
    }
}

void MainMenu::drawTextInputPort()
{
    DrawText("Enter Port ", (int)textBoxPort.x + 50, (int)textBoxPort.y - 30, 20, DARKGRAY);
    DrawText(TextFormat("Current Port: %i", _client->getPort()), (int)textBoxPort.x + 350, (int)textBoxPort.y, 20, DARKGRAY);

    DrawRectangleRec(textBoxPort, LIGHTGRAY);
    if (mouseOnTextPort) DrawRectangleLines((int)textBoxPort.x, (int)textBoxPort.y, (int)textBoxPort.width, (int)textBoxPort.height, RED);
    else DrawRectangleLines((int)textBoxPort.x, (int)textBoxPort.y, (int)textBoxPort.width, (int)textBoxPort.height, DARKGRAY);
    DrawText(namePort, (int)textBoxPort.x + 5, (int)textBoxPort.y + 8, 40, MAROON);
    DrawText(TextFormat("%i/%i", letterCountPort, 20), 1920 / 2 - 400, 290, 20, DARKGRAY);
    if (mouseOnTextPort)
    {
        if (letterCountPort < 20)
        {
            if (((framesCounterPort/20)%2) == 0) DrawText("_", (int)textBoxPort.x + 8 + MeasureText(namePort, 40), (int)textBoxPort.y + 12, 40, MAROON);
        }
    }
}

void MainMenu::draw()
{
    for (auto &image : _images)
        image->draw();
    for (auto &button : _buttons)
        button->draw();
    for (int index = 1; index < _texts.size(); index = index + 1) {
        _texts.at(index)->draw();
    }
    if (_shouldPrintConnectionFailed) {
        _texts.at(0)->draw();
    }
    drawTextInputIp();
    drawTextInputPort();
}

void MainMenu::handleEventTextInputIp()
{
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;
    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letterCount < 20)) {
                name[letterCount] = (char)key;
                name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }
            key = GetCharPressed();  // Check next character in the queue
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER)) {
            std::string tmp(name);
            _client->setMachine(tmp);
            _client->setup();
            memset(name, 0, 20);
            letterCount = 0;
            std::cout << name << std::endl;
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    if (mouseOnText) framesCounter++;
    else framesCounter = 0;
}

void MainMenu::handleEventTextInputPort()
{
    if (CheckCollisionPointRec(GetMousePosition(), textBoxPort)) mouseOnTextPort = true;
    else mouseOnTextPort = false;
    if (mouseOnTextPort) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letterCountPort < 20)) {
                namePort[letterCountPort] = (char)key;
                namePort[letterCountPort+1] = '\0'; // Add null terminator at the end of the string.
                letterCountPort++;
            }
            key = GetCharPressed();  // Check next character in the queue
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCountPort--;
            if (letterCountPort < 0) letterCountPort = 0;
            namePort[letterCountPort] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER)) {
            _client->setPort(std::atoi(namePort));
            _client->setup();
            memset(namePort, 0, 20);
            letterCountPort = 0;
            std::cout << namePort << std::endl;
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    if (mouseOnTextPort) framesCounter++;
    else framesCounterPort = 0;
}

Scenes MainMenu::handleEvent()
{
    _nextScene = Scenes::MAIN_MENU;
    for (auto &button : _buttons)
        button->checkHover(GetMousePosition());
    handleEventTextInputIp();
    handleEventTextInputPort();
    return _nextScene;
}


