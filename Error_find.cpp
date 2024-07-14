/*
** EPITECH PROJECT, 2024
** NanoTekSpice
** File description:
** Error_find.cpp
*/

#include "include/Core/Error_find.hpp"

ErrorFind::ErrorFind(std::ostream &os, const std::string &str) throw() : Error(os, str) {}

ErrorFind::~ErrorFind(void) throw() {}