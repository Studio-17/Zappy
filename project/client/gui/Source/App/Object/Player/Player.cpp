/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#include "Player.hpp"
#include "raymath.h"

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
    _scale = 7.0f;
    _speed = 0.6f;
    _playerId = playerId;
    _level = 1;
    _playerOrientation = playerOrientation;
    _teamName = teamName;
    _camera = camera;
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

void Object::Player::move(Position const &position, Position const &direction)
{
    animation(0);

    _model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD * direction.getX(), DEG2RAD * direction.getY(), DEG2RAD * direction.getZ()});
    Position tmp = position;
    _position += (tmp * _speed);
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

void Object::Player::draw()
{
    Vector2 textPosition = GetWorldToScreen((Vector3){_position.getX(), _position.getY() + 30, _position.getZ()}, _camera->getCamera());
    _camera->endMode3D();
    DrawText(_teamName.c_str(), (int)textPosition.x - MeasureText(_teamName.c_str(), 20)/2, (int)textPosition.y, 20, BLACK);
    _camera->startMode3D();
    if (_isEnable)
        DrawModel(_model, getPosition().getVector3(), _scale, WHITE);
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

void Object::Player::setInventory(std::vector<std::pair<Object::PLAYER_RESOURCES, int>> const &inventory)
{
    _inventory = inventory;
}
