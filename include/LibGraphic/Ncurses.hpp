/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ncurse
*/

#ifndef NCURSE_HPP_
    #define NCURSE_HPP_

    #include <ncurses.h>
    #include <memory>
    #include "../Core/IDisplayModule.hpp"

class ncurse : public Arcade::IDisplayModule
{
    WINDOW *window;
    SCREEN *screen;

    public:
        void Screen();
        void Window(size_t width, size_t height);
        void SetWindowProperties();
        void InitializeWindow(size_t width, size_t height);
        void Destroy() override;
        void Clear(bool menu) override;
        void Draw(std::vector<std::pair<int, int>> _wall, std::vector<std::pair<int, int>> _apple, std::vector<std::pair<int, int>> _snake, std::vector<std::pair<int, int>> _empty, int score, int best_score) override;
        int ConvertColorToPair(Arcade::color_t color);
        void Update() override;
        void DrawText(std::vector<Arcade::text_t> text, int size) override;
        void Sleep() override;
        Arcade::Inputs Input() const override;
        void DrawRectangles(const std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t color) override;
        void LoadBackground(const std::string& imagePath) override;

        ~ncurse();
    protected:
    private:
};

#endif /* !LNCURSE_HPP_ */
