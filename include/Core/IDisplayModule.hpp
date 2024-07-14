/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IDisplayModule.hpp
*/

#ifndef IDISPLAYMODULE_HPP_
    #define IDISPLAYMODULE_HPP_

    #include <iostream>
    #include <vector>
    #include <unordered_map>

namespace Arcade {

    struct position_t {
        float x;
        float y;
    };

    struct text_t {
        std::string text;
        position_t pos;
    };

    struct rectangle_t {
        int x;
        int y;
        int width;
        int height;
    };

    struct color_t {
        int r;
        int g;
        int b;
        int a;
    };

    enum class Inputs {
        UP = 1,
        DOWN,
        A,
        Z,
        R,
        T,
        U,
        E,
        I,
        O,
        P,
        Q,
        S,
        D,
        F,
        G,
        H,
        J,
        K,
        L,
        M,
        W,
        X,
        C,
        V,
        Y,
        B,
        N,
        ENTER,
        SPACE,
        ESC,
        BACKSPACE,
        UNKNOWN = -1
    };

    class IDisplayModule {
        public :
            virtual void LoadBackground(const std::string& imagePath) = 0;
            virtual void Window(size_t width, size_t height) = 0;
            virtual void Draw(std::vector<std::pair<int, int>> _wall, std::vector<std::pair<int, int>> _apple, std::vector<std::pair<int, int>> _snake, std::vector<std::pair<int, int>> _empty, int score, int best_score) = 0;
            virtual void Clear(bool menu) = 0;
            virtual void DrawRectangles(const std::vector<rectangle_t>& rectangles, color_t color) = 0;
            virtual void Update() = 0;
            virtual void Destroy() = 0;
            virtual void DrawText(std::vector<Arcade::text_t> text, int size) = 0;
            virtual Inputs Input() const = 0;
            virtual void Sleep() = 0;
            virtual ~IDisplayModule() = default;
    };
}

#endif /* !IDISPLAYMODULE_HPP_ */