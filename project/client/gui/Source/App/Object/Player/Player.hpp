/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <utility>

    #include "AThreeDimensionObject.hpp"
    #include "Text.hpp"
    #include "Camera.hpp"

namespace Object {
    /**
     * @brief Player class
     */

    enum class ORIENTATION {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    class Player : public AThreeDimensionObject {
        public:
            /**
             * @brief Construct a new Player object
             *
             * @param pathToResources pair of path to resources texture and model
             * @param pathToAnimation path to resource animation
             * @param nbAnimation number of animation
             * @param position 3 dimensional Position
             * @param type map object type
             */
            Player(std::pair<std::string, std::string> const &pathToResources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position, Object::MAP_OBJECTS type);
            /**
             * @brief Construct a new Player object
             *
             * @param pathToModel path to resource model
             * @param pathToResources path to resource texture
             * @param pathToAnimation path to resource animation
             * @param numberOfAnimations number of animation
             * @param position 3 dimensional Position
             * @param type map object type
             */
            Player(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToResources, Object::Render::MyAnimation &pathToAnimation, unsigned int numberOfAnimations, Position const &position, Object::MAP_OBJECTS type, int playerId, ORIENTATION playerOrientation, std::string teamName, std::shared_ptr<RayLib::CinematicCamera> camera);
            /**
             * @brief Destroy the Player object
             */
            ~Player() override;

            void draw() override;
            /**
             * @brief Player Animation
             *
             * @param animNb number of animation
             */
            void animation(std::size_t animNb);
            /**
             * @brief Move player
             *
             * @param position player position
             * @param direction new player position
             */
            void move(Position const &position, Position const &direction);

            /**
             * @brief Set life player
             */
            void die() { _isAlive = false; };
            /**
             * @brief Check if player is dead
             *
             * @return true
             * @return false
             */
            bool isAlive() { return _isAlive; };

            /**
             * @brief Get player speed
             *
             * @return float
             */
            float getSpeed() const { return _speed; };
            /**
             * @brief Set player speed
             *
             * @param addSpeed add speed
             */
            void setSpeed(bool addSpeed);

            /**
             * @brief Get if player is moving
             *
             * @return true
             * @return false
             */
            bool getIsMoving() const { return _isMoving; };
            /**
             * @brief Set is moving player value
             *
             * @param isMoving bool isMoving value
             */
            void setIsMoving(bool isMoving);

            /**
             * @brief Get the Player Id
             *
             * @return int
             */
            int getPlayerId() { return _playerId; };

            /**
             * @brief Get the Player Level
             *
             * @return int
             */
            int getLevel() { return _level; };
            /**
             * @brief Set the Player Level
             *
             * @param level int value level
             */
            void setLevel(int level);

            /**
             * @brief Get the Inventory
             *
             * @return std::vector<PLAYER_RESOURCES, int>
             */
            std::vector<std::pair<PLAYER_RESOURCES, int>> getInventory() { return _inventory; };
            /**
             * @brief Set the Inventory
             *
             * @param inventory inventory resources
             */
            void setInventory(std::vector<std::pair<Object::PLAYER_RESOURCES, int>> const &inventory);

            void setOrientation(enum Object::ORIENTATION);

        private:

            std::pair<float, float> _defaultSpeed = {0.5f, 0.8f};

            float _speed;

            float _scale;
            int _life;
            bool _isAlive = true;
            bool _isMoving = false; ///< is moving
            int _playerId;
            int _level;

            std::vector<std::pair<PLAYER_RESOURCES, int>> _inventory;
            ORIENTATION _playerOrientation;
            std::string _teamName;
            std::shared_ptr<RayLib::CinematicCamera> _camera;
    };
}

#endif /* !PLAYER_HPP_ */
