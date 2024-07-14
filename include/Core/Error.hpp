/*
** EPITECH PROJECT, 2024
** NanoTekSpice
** File description:
** Error.hpp
*/

#ifndef ERROR_HPP_
	#define ERROR_HPP_

	#include <exception>
	#include <iostream>
	#include <string>

class Error: public std::exception {
    public:
        Error(std::ostream &os, const std::string &str) throw();
        virtual ~Error(void) throw();
        const char *what(void) const throw();
    private:
        std::string info;
        std::ostream &ostream;
};

#endif /* !ERROR_HPP_ */