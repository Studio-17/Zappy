/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** Button
*/

#include "Button.hpp"

Object::Button::Button(std::string const &buttonPath, int nbFrame, Position const &position) : _isEnable(true), 
    _isClickable(true),
    _nbFrame(nbFrame), _state(Default), _position(position), _buttonTexture(LoadTexture(buttonPath.c_str())), _frameHeight((float)_buttonTexture.height/_nbFrame), _isAudio(false),
    _sourceRec({ 0, 0, (float)_buttonTexture.width, (float)_buttonTexture.height / _nbFrame }),
    _buttonRect({ _position.getX(),  _position.getY(), (float)_buttonTexture.width, (float)_buttonTexture.height / _nbFrame}),
    _callBack(nullptr)
{
}

Object::Button::Button(std::string const &buttonPath, int nbFrame, std::function<void(void)> callBack, Position const &position) : _isEnable(true),
    _isClickable(true),
    _nbFrame(nbFrame), _position(position), _buttonTexture(LoadTexture(buttonPath.c_str())), _frameHeight((float)_buttonTexture.height/_nbFrame), _isAudio(false), _callBack(callBack),
    _sourceRec({ 0, 0, (float)_buttonTexture.width, (float)_buttonTexture.height / _nbFrame }),
    _buttonRect({ _position.getX(),  _position.getY(), (float)_buttonTexture.width, (float)_buttonTexture.height / _nbFrame})
{
}

Object::Button::~Button()
{
    UnloadTexture(_buttonTexture);
}

void Object::Button::draw()
{
    if (_nbFrame == 2 && _state == Button::State::Click)
        _sourceRec.y = _frameHeight;
    else
        _sourceRec.y = _state * _frameHeight;
    if (_isEnable) {
        DrawTextureRec(_buttonTexture, _sourceRec, (Vector2){ _buttonRect.x, _buttonRect.y }, WHITE); // Draw button frame
        _text.draw();
        _image.draw();
    }
}

void Object::Button::enable()
{
    _isEnable = true;
}

void Object::Button::disable()
{
    _isEnable = false;
}

bool Object::Button::isEnable() const
{
    return _isEnable;
}

void Object::Button::enableClick()
{
    _isClickable = true;
}

void Object::Button::disableClick()
{
    _isClickable = false;
}

bool Object::Button::isClickable() const
{
    return _isClickable;
}

void Object::Button::setPosition(Position const &position)
{
    _position = position;
}

void Object::Button::setPosition(float x, float y)
{
    _position.setPosition(x, y);
}

void Object::Button::setPosition(float x, float y, float z)
{
    _position.setPosition(x, y, z);
}

Position Object::Button::getPosition() const
{
    return _position;
}

void Object::Button::setText(std::string const &text)
{
    _text.setText(text);
}

std::string Object::Button::getText() const
{
    return _text.getText();
}

void Object::Button::setTextPosition(Position const &position)
{
    _text.setPosition(position);
}

void Object::Button::setTextPosition(float x, float y)
{
    _text.setPosition(x, y);
}

Position Object::Button::getTextPosition() const
{
    return _text.getPosition();
}


void Object::Button::setCallBack(std::function<void(void)> callBack)
{
    _callBack = callBack;
}

bool Object::Button::onClick()
{
    if (_state == Click)
       return true;
    return false;
}

bool Object::Button::onHover()
{
    if (_state == Hover)
        return true;
    return false;
}

void Object::Button::checkHover(Vector2 const &mousePosition, bool alreadyHovered)
{
    if (CheckCollisionPointRec(mousePosition, _buttonRect)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                _state = Click;
        else
                _state = Hover;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && _isClickable) {
            if (_callBack)
                _callBack();
        }
    }
    else {
        if (alreadyHovered)
                _state = Hover;
        else
            _state = Default;
    }
}

void Object::Button::setHover()
{
    _state = Hover;
}

void Object::Button::unsetHover()
{
    _state = Default;
}

void Object::Button::click()
{
    _state = Click;
    if (_callBack && _isClickable)
        _callBack();
}

