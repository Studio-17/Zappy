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

Object::Player::Player(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToResources, Object::Render::MyAnimation &pathToAnimation, unsigned int numberOfAnimations, Position const &position, Object::MAP_OBJECTS type, int playerId, ORIENTATION playerOrientation, std::string teamName, std::shared_ptr<RayLib::CinematicCamera> camera, int mapWidth, int mapHeight) :
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
    _levelTwoTexture = LoadTexture("Resources/Players/white.png");
    _levelThreeTexture = LoadTexture("Resources/Players/purple.png");
    _texturePlayersLevel = {
                {0, _texture},
                {1, _levelTwoTexture},
                {2, _levelThreeTexture}
    };
    _mapWidth = mapWidth;
    _mapHeight = mapHeight;
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
    _currentAnimation = 0;
    _directionToMove = _position - position;
    _currentPositionMove = position;
    if (!_isMoving)
        _isMoving = true;
    _replacedPlayer = false;
}

void Object::Player::continueMoving()
{
    if (getPosition() == _currentPositionMove || _replacedPlayer == true) {
        _isMoving = false;
        _currentAnimation = 1;
        return;
    }

    if (_directionToMove.getX() != 0 && _playerOrientation == Object::ORIENTATION::EAST) {
        if (_position.getX() + 10 == _mapWidth * 10) {
            setPosition(Position(0, _position.getY(), _position.getZ()));
            _replacedPlayer = true;
        }
        setPosition(Position(_position.getX() + 0.5, _position.getY(), _position.getZ()));
        if (getPosition().getX() >= _currentPositionMove.getX() || _replacedPlayer == true) {
            _isMoving = false;
            _currentAnimation = 1;
            setPosition(_currentPositionMove);
            return;
        }
    }
    if (_directionToMove.getX() != 0 && _playerOrientation == Object::ORIENTATION::WEST) {
        if (_position.getX() - 10 == -10) {
            setPosition(Position((_mapWidth - 1) * 10, _position.getY(), _position.getZ()));
            _replacedPlayer = true;
        }
        setPosition(Position(_position.getX() - 0.5, _position.getY(), _position.getZ()));
        if (getPosition().getX() <= _currentPositionMove.getX() || _replacedPlayer == true) {
            _isMoving = false;
            _currentAnimation = 1;
            setPosition(_currentPositionMove);
            return;
        }
    }
    if (_directionToMove.getZ() != 0 && _playerOrientation == Object::ORIENTATION::NORTH) {
        if (_position.getZ() - 10 == -10) {
            setPosition(Position(_position.getX(), _position.getY(), (_mapHeight - 1) * 10));
            _replacedPlayer = true;
        }
        setPosition(Position(_position.getX(), _position.getY(), _position.getZ() - 0.5));
        if (getPosition().getZ() <= _currentPositionMove.getZ() || _replacedPlayer == true) {
            _isMoving = false;
            _currentAnimation = 1;
            setPosition(_currentPositionMove);
            return;
        }
    }
    if (_directionToMove.getZ() != 0 && _playerOrientation == Object::ORIENTATION::SOUTH) {
        if (_position.getZ() + 10 == _mapHeight * 10) {
            setPosition(_position.getX(), _position.getY(), 0);
            _replacedPlayer = true;
        }
        setPosition(Position(_position.getX(), _position.getY(), _position.getZ() + 0.5));
        if (getPosition().getZ() >= _currentPositionMove.getZ() || _replacedPlayer == true) {
            _isMoving = false;
            _currentAnimation = 1;
            setPosition(_currentPositionMove);
            return;
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
    _playerOrientation = orientation;
}

void Object::Player::handleEvent()
{
    _boundingBox = {(BoundingBox){(Vector3){ getPosition().getX() - 5, getPosition().getY(), getPosition().getZ() - 5 },
            (Vector3){ getPosition().getX() + 5, getPosition().getY() + 10, getPosition().getZ() + 5 }}};
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (!_playerCollision.hit) {
            _mouseRay = GetMouseRay(GetMousePosition(), _camera->getCamera());
            _playerCollision = GetRayCollisionBox(_mouseRay, _boundingBox);
            _isClicked = false;
        }
        else {
            _isClicked = true;
            _playerCollision.hit = false;
        }

    }
    if (_isMoving)
        continueMoving();
}

void Object::Player::draw()
{
    Vector2 textPosition = GetWorldToScreen((Vector3){_position.getX(), _position.getY() + 30, _position.getZ()}, _camera->getCamera());
    DrawText(_teamName.c_str(), (int)textPosition.x - MeasureText(_teamName.c_str(), 20)/2, (int)textPosition.y, 20, BLACK);
    _camera->startMode3D();
    if (_isEnable)
        DrawModel(_model, getPosition().getVector3(), _scale, WHITE);
    _camera->endMode3D();
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
    _startedIncantation = true;
    _currentAnimation = 5;
}

void Object::Player::stopIncantation(int level)
{
    _currentAnimation = 1;
    _level = level;
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texturePlayersLevel.at(level - 1);
    _startedIncantation = false;
}
