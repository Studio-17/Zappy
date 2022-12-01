/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** ClientErrors
*/

#ifndef CLIENTERRORS_HPP_
#define CLIENTERRORS_HPP_

#include "Errors.hpp"

class ClientErrors : public Errors
{
    public:
        ClientErrors(std::string const &message);
        virtual ~ClientErrors();

    protected:
    private:
};

#endif /* !CLIENTERRORS_HPP_ */
