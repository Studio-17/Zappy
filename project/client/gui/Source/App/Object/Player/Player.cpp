/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#include "Player.hpp"

Object::Player::Player(std::pair<std::string, std::string> const &pathToResources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position, Object::MAP_OBJECTS type) :
    AThreeDimensionObject(pathToResources, pathToAnimation, nbAnimation, position, type)
{
    _scale = 7.0f;
    _speed = 0.6f;
    _level = 1;
}

Object::Player::Player(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToResources, Object::Render::MyAnimation &pathToAnimation, unsigned int numberOfAnimations, Position const &position, Object::MAP_OBJECTS type, int playerId, ORIENTATION playerOrientation, std::string teamName, std::shared_ptr<RayLib::CinematicCamera> camera) :
    AThreeDimensionObject(pathToModel, pathToResources, pathToAnimation, numberOfAnimations, position, type)
{
    _scale = 5.0f;
    _speed = 0.6f;
    _playerId = playerId;
    _level = 1;
    _playerOrientation = playerOrientation;
    _teamName = teamName;
    _camera = camera;
    _playerInfo._playerLevel = 1;
    _playerInfo._teamName = teamName;
    _playerInfo._inventory = {10, 0, 0, 0, 0, 0, 0};
    setOrientation(_playerOrientation);
}

Object::Player::~Player()
{
}

void Object::Player::animation(std::size_t animNb)
{
    _animFrameCounter++;
    UpdateModelAnimation(_model, _anims[animNb], _animFrameCounter);
    if (_animFrameCounter >= _anims[animNb].frameCount)
        _animFrameCounter = 0;
}

void Object::Player::move(Position const &position)
{
    Position tmp = _position - position;
    Position currentPos = _position;
    std::cout << "tmp: " << tmp << std::endl;
    std::cout << "new position: " << position << std::endl;
    int index = 1;


    _movementClock.start();
    if (tmp.getX() != 0) {
        std::cout << "first if x" << std::endl;
        while (_position.getX() != position.getX()) {
            if (_movementClock.getElapsedTime() > 1000) {
                setPosition(Position(_position.getX() + 1, _position.getY(), _position.getZ()));
                _movementClock.restart();
            }
        }
    }
    if (tmp.getZ() != 0) {
        std::cout << "first if z" << std::endl;
        while (_position.getZ() != position.getZ()) {
            animation(0);
            if (_movementClock.getElapsedTime() > 1000) {
                std::cout << "second if z" << std::endl;
                setPosition(Position(currentPos.getX(), currentPos.getY(), currentPos.getY() + index));
                _movementClock.restart();
                index++;
            }
        }
    }



}

void Object::Player::setOrientation(Object::ORIENTATION orientation)
{
    Vector3 tmp;
    if (orientation == ORIENTATION::NORTH)
        tmp = {0, 90, 0};
    if (orientation == ORIENTATION::EAST)
        tmp = {0, 180, 0};
    if (orientation == ORIENTATION::SOUTH)
        tmp = {0, -90, 0};
    if (orientation == ORIENTATION::WEST)
        tmp = {0, 0, 0};

    _model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * tmp.x, DEG2RAD * tmp.y, DEG2RAD * tmp.z});
}

void Object::Player::handleEvent()
{
    _boundingBox = {(BoundingBox){(Vector3){ getPosition().getX() - 5, getPosition().getY(), getPosition().getZ() - 5 },
            (Vector3){ getPosition().getX() + 5, getPosition().getY() + 10, getPosition().getZ() + 5 }}};
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (!_playerCollision.hit) {
            _mouseRay = GetMouseRay(GetMousePosition(), _camera->getCamera());
            _playerCollision = GetRayCollisionBox(_mouseRay,
            (BoundingBox){(Vector3){ getPosition().getX() - 5, getPosition().getY(), getPosition().getZ() - 5 },
                                              (Vector3){ getPosition().getX() + 10, getPosition().getY() + 5, getPosition().getZ() + 5 }});
            _isClicked = true;
        }
        else {
            _playerCollision.hit = false;
            _isClicked = false;
        }

    }
}

void Object::Player::draw()
{
    Vector2 textPosition = GetWorldToScreen((Vector3){_position.getX(), _position.getY() + 30, _position.getZ()}, _camera->getCamera());
    if (_isEnable)
        DrawModel(_model, getPosition().getVector3(), _scale, WHITE);
    _camera->endMode3D();
    DrawText(_teamName.c_str(), (int)textPosition.x - MeasureText(_teamName.c_str(), 20)/2, (int)textPosition.y, 20, BLACK);
    _camera->startMode3D();
}

void Object::Player::setSpeed(bool addSpeed)
{
    if (addSpeed) {
        if (_speed < _defaultSpeed.second)
            _speed += 0.1f;
    }
    else {
        if (_speed > _defaultSpeed.first)
            _speed -= 0.1f;
    }
}

void Object::Player::setLevel(int level)
{
    _level = level;
}

void Object::Player::setInventory(std::vector<int> const &inventory)
{
    _playerInfo._inventory = inventory;
}

void Object::Player::startIncantation()
{
    _currentAnimation = 5;
}
