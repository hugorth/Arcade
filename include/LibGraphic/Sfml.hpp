/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sfml
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include "../Core/IDisplayModule.hpp"
    #include "../Core/Error_find.hpp"
    #include <SFML/Graphics.hpp>
    #include <memory>

class sfml : public Arcade::IDisplayModule {
    sf::RenderWindow* window;
    sf::Sprite background;

    public:
        void Window(size_t width, size_t height) override;
        void Destroy() override;
        void Clear(bool menu) override;
        void Draw(std::vector<std::pair<int, int>> _wall, std::vector<std::pair<int, int>> _apple, std::vector<std::pair<int, int>> _snake, std::vector<std::pair<int, int>> _empty, int score, int best_score) override;
        void Update() override;
        void DrawText(std::vector<Arcade::text_t> text, int size) override;
        void Sleep() override;
        Arcade::Inputs Input() const override;
        void DrawRectangles(const std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t color) override;
        void LoadBackground(const std::string& imagePath) override;
};

#endif /* !SFML_HPP_ */
