/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** core
*/

#include "include/Core/Core.hpp"
#include <chrono>
#include <dirent.h>
#include <filesystem>
#include <map>
#include <fstream>

Core::Core() : menu(true), select_library(0), select_game(0) {
    scanDirectory("./lib/");
    keyActions[Arcade::Inputs::UP] = [this]() { this->navigateMenuUp(); };
    keyActions[Arcade::Inputs::DOWN] = [this]() { this->navigateMenuDown(); };
    keyActions[Arcade::Inputs::N] = [this]() { this->nextLibrary(); };
    keyActions[Arcade::Inputs::V] = [this]() { this->nextGame(); };
    keyActions[Arcade::Inputs::ENTER] = [this]() { this->selectGame(); };
    keyActions[Arcade::Inputs::ESC] = [this]() { this->returnToMenu(); };
}

void Core::run(std::string lib) {
    loadLib(lib);
    loadGame("");
    gameloop();
}

void Core::displayMenu(void (Core::*drawFunc)(std::vector<Arcade::text_t>&, std::vector<Arcade::rectangle_t>&, Arcade::color_t&)) {
    Arcade::rectangle_t rectangle;
    rectangle.x = 100;
    rectangle.y = 400;
    rectangle.width = 400;
    rectangle.height = 300;

    Arcade::color_t color;
    color.r = 210;
    color.g = 210;
    color.b = 210;
    color.a = 255;

    moduleManager.library->LoadBackground("./Assets/lala.jpg");
    moduleManager.library->DrawText({{"ARCADE", {310, 100}}}, 48);
    std::vector<Arcade::text_t> text;
    std::vector<Arcade::rectangle_t> rectangles;
    for (int i = 0; i < moduleManager.stock_game.size(); i++) {
        std::string lib_name = std::filesystem::path(moduleManager.stock_game[i]).stem().string();
        lib_name = lib_name.substr(7);
        Arcade::text_t textObject{lib_name, Arcade::position_t{350, (float)((i + 1) * 50 + 310)}};
        text.push_back(textObject);

        if (i == select_game) {
            int posX = static_cast<int>(textObject.pos.x);
            int posY = static_cast<int>(textObject.pos.y);
            int width = static_cast<int>(textObject.text.size() * 10 + 20);
            Arcade::rectangle_t rectangle{posX, posY, width, 30};
            rectangles.push_back(rectangle);
        }
    }
    (this->*drawFunc)(text, rectangles, color);
}

void Core::drawSFMLMenu(std::vector<Arcade::text_t>& text, std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t& color) {
    moduleManager.library->DrawRectangles(rectangles, color);
    moduleManager.library->DrawText(text, 24);
}

void Core::drawNcursesMenu(std::vector<Arcade::text_t>& text, std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t& color) {
    moduleManager.library->DrawRectangles(rectangles, color);
    moduleManager.library->DrawText(text, 24);
}

void Core::drawSDL2Menu(std::vector<Arcade::text_t>& text, std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t& color) {
    moduleManager.library->DrawRectangles(rectangles, color);
    moduleManager.library->DrawText(text, 24);
}

void Core::gameloop() {
    Arcade::Inputs key = Arcade::Inputs::UNKNOWN;
    std::string name;
    Arcade::position_t usernamePosition{350, 300};
    std::map<Arcade::Inputs, char> keyToChar = {
        {Arcade::Inputs::UP, 0},
        {Arcade::Inputs::A, 'a'},
        {Arcade::Inputs::B, 'b'},
        {Arcade::Inputs::C, 'c'},
        {Arcade::Inputs::D, 'd'},
        {Arcade::Inputs::E, 'e'},
        {Arcade::Inputs::F, 'f'},
        {Arcade::Inputs::G, 'g'},
        {Arcade::Inputs::H, 'h'},
        {Arcade::Inputs::I, 'i'},
        {Arcade::Inputs::J, 'j'},
        {Arcade::Inputs::K, 'k'},
        {Arcade::Inputs::L, 'l'},
        {Arcade::Inputs::M, 'm'},
        {Arcade::Inputs::N, 'n'},
        {Arcade::Inputs::O, 'o'},
        {Arcade::Inputs::P, 'p'},
        {Arcade::Inputs::Q, 'q'},
        {Arcade::Inputs::R, 'r'},
        {Arcade::Inputs::S, 's'},
        {Arcade::Inputs::T, 't'},
        {Arcade::Inputs::U, 'u'},
        {Arcade::Inputs::V, 'v'},
        {Arcade::Inputs::W, 'w'},
        {Arcade::Inputs::X, 'x'},
        {Arcade::Inputs::Y, 'y'},
        {Arcade::Inputs::Z, 'z'},
        {Arcade::Inputs::SPACE, ' '},
        {Arcade::Inputs::BACKSPACE, 127},
        {Arcade::Inputs::ENTER, '\n'},
        {Arcade::Inputs::ESC, 0},
    };

    while (key != Arcade::Inputs::ENTER) {
        key = moduleManager.library->Input();
        auto it = keyToChar.find(key);
        if (it != keyToChar.end()) {
            if (it->second == 127 && !name.empty()) {
                name.pop_back();
            } else if (it->second != 127) {
                name += it->second;
            }
        }
        moduleManager.library->Clear(true);
        Arcade::text_t usernameObject{name, usernamePosition}; 
        moduleManager.library->DrawText({{"ARCADE", {310, 100}}}, 48);
        moduleManager.library->DrawText({{"Username : ", {80, 300}}}, 48);
        moduleManager.library->DrawText({usernameObject}, 48);
        moduleManager.library->Update();
    }

    std::ofstream outFile("Assets/username.txt");
    if (outFile.is_open()) {
        outFile << name;
        outFile.close();
    } else {
        std::cout << "Unable to open file";
    }
    key = Arcade::Inputs::UNKNOWN;

    while (key != Arcade::Inputs::A) {
        key = moduleManager.library->Input();
        auto action = keyActions.find(key);
        if (action != keyActions.end())
            action->second();
        moduleManager.library->Clear(menu);
        if (menu) {
            if (moduleManager._currentLib == "./lib/arcade_sfml.so") {
                displayMenu(&Core::drawSFMLMenu);
            } else if (moduleManager._currentLib == "./lib/arcade_sdl2.so") {
                displayMenu(&Core::drawSDL2Menu);
            } else {
                displayMenu(&Core::drawNcursesMenu);
            }
        } else {
            moduleManager.game->Input(key);
            moduleManager.game->Draw(*moduleManager.library);
            moduleManager.game->Logic();
            moduleManager.library->Sleep();
        }
        moduleManager.library->Update();
    }
    moduleManager.library->Destroy();
}

void Core::loadLib(std::string current_lib) {
    if (moduleManager.library != nullptr)
        moduleManager.library->Destroy();
    moduleManager.library = loadModule<Arcade::IDisplayModule, C_encapsulation>(current_lib, moduleManager.library_encapsulation, moduleManager.stock_library, select_library, "Lib");
    moduleManager.library->Window(800, 600);
}

void Core::loadGame(std::string current_game) {
    moduleManager.game = loadModule<Arcade::IGameModule, C_encapsulation>(current_game, moduleManager.game_encapsulation, moduleManager.stock_game, select_game, "Game");
}

void Core::scanDirectory(const std::string& path) {
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] == '.')
                continue;
            std::string fullpath = path + ent->d_name;
            if (isValidLibrary(fullpath, "Game"))
                moduleManager.stock_game.push_back(fullpath);
            else if (isValidLibrary(fullpath, "Lib"))
                moduleManager.stock_library.push_back(fullpath);
        }
        closedir(dir);
    }
}

bool Core::isValidLibrary(const std::string& path, const std::string& entryPoint) {
    std::unique_ptr<C_encapsulation> loader = std::make_unique<C_encapsulation>();
    void* handle = loader->dlopenC(path, RTLD_LAZY);
    if (!handle)
        throw ErrorFind(std::cerr, "Error: " + loader->dlerrorC());
    void* symbol = loader->dlsymC(handle, entryPoint);
    if (!symbol) {
        loader->dlcloseC(handle);
        return false;
    }
    loader->dlcloseC(handle);
    return true;
}

Core::~Core() {}
