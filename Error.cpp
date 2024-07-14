/*
** EPITECH PROJECT, 2024
** NanoTekSpice
** File description:
** Error.cpp
*/

#include "include/Core/Error.hpp"

Error::Error(std::ostream &os, const std::string &str) throw() : ostream(os)
{
	info = str;
}

Error::~Error(void) throw() {}

const char *Error::what(void) const throw()
{
	return info.c_str();
}