/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <exception>
#include <iostream>
#include <string>

class Errors : public std::exception
{
    public:
        Errors(std::string const &message) throw();
        virtual ~Errors() throw();

        const char *what() const throw();

    protected:
    private:
        std::string _message;
};

#endif /* !ERRORS_HPP_ */
