/*
** EPITECH PROJECT, 2024
** NanoTekSpice
** File description:
** Error_find.hpp
*/

#ifndef ERROR_FIND_HPP_
	#define ERROR_FIND_HPP_

	#include "Error.hpp"

class ErrorFind: public Error {
    public:
        ErrorFind(std::ostream &os, const std::string &str) throw();
        virtual ~ErrorFind(void) throw();
};

#endif /* !ERROR_FIND_HPP_ */