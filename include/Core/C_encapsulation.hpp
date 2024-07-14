/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** C_encapsulation.hpp
*/

#ifndef C_ENCAPSULATION_HPP_
    #define C_ENCAPSULATION_HPP_

    #include <iostream>
    #include <dlfcn.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <string>
    #include <cstring>

class C_encapsulation {
public:
    C_encapsulation() = default;
    ~C_encapsulation() = default;
    void *dlopenC(const std::string& args, int flag);
    void *dlsymC(void *handle, const std::string& args);
    int dlcloseC(void *handle);
    std::string dlerrorC();

private:
    void* _handle = nullptr;
};

#endif /* !C_ENCAPSULATION_HPP_ */
