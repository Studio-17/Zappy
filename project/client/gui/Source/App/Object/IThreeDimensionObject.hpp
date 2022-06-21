/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-martin.vanaud
** File description:
** IThreeDimensionObject
*/

#ifndef ITHREEDIMENSIONOBJECT_HPP_
    #define ITHREEDIMENSIONOBJECT_HPP_

    #include "IObject.hpp"

namespace Object
{
    /**
     * @brief enum of 3D object type present in map
     */
    enum class MAP_OBJECTS {
        TILES,
        PLAYER,
        RESSOURCES,
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };

    /**
     * @brief An interface of every three dimensional object
     */
    class IThreeDimensionObject : public IObject {
        public:
            /**
             * @brief Destroy the IThreeDimensionObject object
             */
            virtual ~IThreeDimensionObject() = default;

            /**
             * @brief draw a three dimensional object
             */
            virtual void draw() = 0;

            virtual void enable() = 0;
            virtual void disable() = 0;
            virtual bool isEnable() const = 0;

            virtual void setPosition(Position const &position) = 0;
            virtual void setPosition(float x, float y) = 0;
            virtual void setPosition(float x, float y, float z) = 0;

        protected:
        private:
    };
}

#endif /* !ITHREEDIMENSIONOBJECT_HPP_ */
