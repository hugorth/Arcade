/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** main
*/

#include <iostream>
#include "include/Core/Core.hpp"

int main(int ac, char **av) {
    if (ac != 2)
        throw ErrorFind(std::cerr, "Usage: ./arcade [lib]");
    Core core;
    core.moduleManager._currentLib = av[1];
    core.run(av[1]);
    return 0;
}
