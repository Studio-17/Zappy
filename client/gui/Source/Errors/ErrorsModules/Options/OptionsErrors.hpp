/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** OptionsErrors
*/

#ifndef OPTIONSERRORS_HPP_
#define OPTIONSERRORS_HPP_

#include "Errors.hpp"

class OptionsErrors : public Errors
{
    public:
        OptionsErrors(std::string const &message);
        virtual ~OptionsErrors();

    protected:
    private:
};

#endif /* !OPTIONSERRORS_HPP_ */
