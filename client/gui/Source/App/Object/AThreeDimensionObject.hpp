/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** AThreeDimensionObject
*/

#ifndef ATHREEDIMENSIONOBJECT_HPP_
    #define ATHREEDIMENSIONOBJECT_HPP_

    #include <raylib.h>
    #include <vector>
    #include "raymath.h"


    #include "Rendering/Animation.hpp"
    #include "Rendering/Model.hpp"
    #include "Rendering/Texture.hpp"

    #include "IThreeDimensionObject.hpp"

namespace Object
{

    /**
     * @brief enum for the player's resources
     */
    enum class PLAYER_RESOURCES {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
        NB_RESOURCES
    };

    /**
     * @brief An abstract class of every three dimensional object
     */
    class AThreeDimensionObject : public IThreeDimensionObject
    {
    public:
        // Non Animated
        /**
         * @brief Construct a new AThreeDimensionObject object (non animated)
         *
         * @param pathToResources pair of path to resources texture and model
         * @param position 3 dimensional Position
         * @param type map object type
         */
        AThreeDimensionObject(std::pair<std::string, std::string> const &pathToResources, Position const &position, Object::MAP_OBJECTS type);
        /**
         * @brief Construct a new AThreeDimensionObject object (non animated)
         *
         * @param pathToModel path to resource model
         * @param pathToTexture path to resource texture
         * @param position 3 dimensional Position
         * @param type map object type
         */
        AThreeDimensionObject(Object::Render::MyModel pathToModel, Object::Render::MyTexture pathToTexture, Position const &position, Object::MAP_OBJECTS type);

        /**
         * @brief Construct a new AThreeDimensionObject object
         *
         * @param pathToModel path to resource model
         * @param position 3 dimensional Position
         * @param type map object type
         */
        AThreeDimensionObject(Object::Render::MyModel pathToModel, Position const &position, Object::MAP_OBJECTS type);

        // Animated
        /**
         * @brief Construct a new AThreeDimensionObject object (animated)
         *
         * @param pathToResources pair of path to resources texture and model
         * @param pathToAnimation  path to resource animation
         * @param nbAnimation number of animation
         * @param position 3 dimensional Position
         * @param type map object type
         */
        AThreeDimensionObject(std::pair<std::string, std::string> const &pathToResources, std::string const &pathToAnimation, unsigned int nbAnimation, Position const &position, Object::MAP_OBJECTS type);
        /**
         * @brief Construct a new AThreeDimensionObject object (animated)
         *
         * @param pathToModel path to resource model
         * @param pathToTexture path to resource texture
         * @param pathToAnimation path to resource animation
         * @param numberOfAnimations number of animation
         * @param position 3 dimensional Position
         * @param type map object type
         */
        AThreeDimensionObject(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToTexture, Object::Render::MyAnimation &pathToAnimation, unsigned int numberOfAnimations, Position const &position, Object::MAP_OBJECTS type);


        /**
         * @brief Destroy the AThreeDimensionObject object
         */
        virtual ~AThreeDimensionObject() = default;

        virtual void draw() = 0;

        virtual void enable() override;
        virtual void disable() override;
        virtual bool isEnable() const override;

        void setPosition(Position const &position) override;
        void setPosition(float x, float y) override;
        void setPosition(float x, float y, float z) override;
        Position getPosition() const;

        /**
         * @brief Get the Texture object
         *
         * @return Texture2D texture from raylib
         */
        Texture2D getTexture() const;
        /**
         * @brief Get the Model object
         *
         * @return Model model from raylib
         */
        Model getModel() const;
        /**
         * @brief Get 3 dimensional dimension object
         *
         * @return Position 3 dimensional Position
         */
        Position getDimensions() const;
        /**
         * @brief Get the scale object
         *
         * @return float float scale value
         */
        float getScale() const;
        /**
         * @brief Set the scale object
         *
         * @param scale float scale value
         */
        void setScale(float scale);

        /**
         * @brief Get the map object type
         *
         * @return Object::MAP_OBJECTS enum of map object type
         */
        Object::MAP_OBJECTS getType() const { return _type; };

    protected:
        bool _isEnable; ///< object is enable
        Texture2D _texture; ///< texture from raylib
        Model _model; ///< model from raylib

        Position _position; ///< 3 dimensional Position
        Position _dimensions; ///< 3 dimensional dimension
        bool _isAnimated; ///< object is animated

        unsigned int _animsCount = 0; ///< number of animation
        int _animFrameCounter = 0; ///< animation frame counter
        ModelAnimation *_anims; ///< model animation from raylib
        Object::MAP_OBJECTS _type; ///< map object type

        float _scale = 0.5f; ///< scale value
    private:
    };
}

#endif /* !ATHREEDIMENSIONOBJECT_HPP_ */
