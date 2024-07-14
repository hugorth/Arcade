/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** C_encapsulation
*/

#include "include/Core/C_encapsulation.hpp"

void *C_encapsulation::dlopenC(const std::string& args, int flag) {
    _handle = dlopen(args.c_str(), flag);
    return _handle;
}

void *C_encapsulation::dlsymC(void *handle, const std::string& args) {
    return dlsym(handle, args.c_str());
}

int C_encapsulation::dlcloseC(void *handle) {
    return dlclose(handle);
}

std::string C_encapsulation::dlerrorC() {
    return dlerror();
}
