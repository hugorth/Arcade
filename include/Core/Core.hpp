/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core.hpp
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <memory>
    #include <vector>
    #include <string>
    #include <unordered_map>
    #include <functional>
    #include "IGameModule.hpp"
    #include "IDisplayModule.hpp"
    #include "C_encapsulation.hpp"
    #include "Error.hpp"
    #include "Error_find.hpp"

class Core {
    int select_library;
    int select_game;
    bool menu;
    void loadLib(std::string lib);
    void loadGame(std::string game);
    void scanDirectory(const std::string& path);
    bool isValidLibrary(const std::string& path, const std::string& entryPoint);

    void drawSFMLMenu(std::vector<Arcade::text_t>& text, std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t& color);
    void drawSDL2Menu(std::vector<Arcade::text_t>& text, std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t& color);
    void drawNcursesMenu(std::vector<Arcade::text_t>& text, std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t& color);

public:
    struct ModuleManager {
        std::unique_ptr<C_encapsulation> library_encapsulation;
        std::unique_ptr<C_encapsulation> game_encapsulation;
        std::unique_ptr<Arcade::IDisplayModule> library;
        std::unique_ptr<Arcade::IGameModule> game;
        std::vector<std::string> stock_library;
        std::vector<std::string> stock_game;
        std::string _currentLib;
    } moduleManager;
    Core();
    void run(std::string lib);
    void displayMenu(void (Core::*drawFunc)(std::vector<Arcade::text_t>&, std::vector<Arcade::rectangle_t>&, Arcade::color_t&));
    void gameloop();
    ~Core();

private:
    std::unordered_map<Arcade::Inputs, std::function<void()>> keyActions;

    template<typename TModule, typename TLoader>
    std::unique_ptr<TModule> loadModule(const std::string& moduleName, std::unique_ptr<TLoader>& loader, std::vector<std::string>& modules, int& moduleIndex, const std::string& entryPoint) {
        void* handle;
        if (moduleName == "") {
            loader = std::make_unique<C_encapsulation>();
            handle = loader->dlopenC(modules[moduleIndex], RTLD_LAZY);
        } else {
            while (moduleName != modules[moduleIndex])
                moduleIndex = (moduleIndex + 1) % modules.size();
            loader = std::make_unique<C_encapsulation>();
            handle = loader->dlopenC(moduleName, RTLD_LAZY);
        }
        if (!handle)
            throw ErrorFind(std::cerr, "Error: " + loader->dlerrorC());
        TModule* (*entryPointFunc)() = reinterpret_cast<TModule* (*)()>(loader->dlsymC(handle, entryPoint));
        if (!entryPointFunc) {
            throw ErrorFind(std::cerr, "Error: " + loader->dlerrorC());
            loader->dlcloseC(handle);
        }
        return std::unique_ptr<TModule>(entryPointFunc());
    }

    void navigateMenuUp() {
        if (menu)
            select_game = (select_game - 1 + moduleManager.stock_game.size()) % moduleManager.stock_game.size();
    }

    void navigateMenuDown() {
        if (menu)
            select_game = (select_game + 1) % moduleManager.stock_game.size();
    }

    void nextLibrary() {
        select_library = (select_library + 1) % moduleManager.stock_library.size();
        loadLib("");
    }

    void nextGame() {
        select_game = (select_game + 1) % moduleManager.stock_game.size();
        loadGame("");
    }

    void selectGame() {
        if (!menu) return;
        std::string selectedGamePath = moduleManager.stock_game[select_game];
        loadGame(selectedGamePath);
        menu = false;
    }

    void returnToMenu() {
        if (menu) return;
        menu = true;
    }
};

#endif /* !CORE_HPP_ */
