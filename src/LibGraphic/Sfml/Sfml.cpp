/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sfml
*/

#include "../../../include/LibGraphic/Sfml.hpp"
#include "../../../include/Core/IGameModule.hpp"

extern "C" Arcade::IDisplayModule *Lib()
{
    return new sfml();
}

void sfml::Window(size_t width, size_t height)
{
    window = new sf::RenderWindow(sf::VideoMode(width, height), "", sf::Style::Default);
}

void sfml::Clear(bool menu)
{
    window->clear();
}

void sfml::Update()
{
    window->display();
}

void sfml::Destroy()
{
    window->close();
}

void sfml::Draw(std::vector<std::pair<int, int>> _wall, std::vector<std::pair<int, int>> _apple, std::vector<std::pair<int, int>> _snake, std::vector<std::pair<int, int>> _empty, int score, int best_score)
{
    int size = 20;
    sf::RectangleShape wall(sf::Vector2f(size, size));
    sf::RectangleShape apple(sf::Vector2f(size, size));
    sf::RectangleShape snake(sf::Vector2f(size, size));
    sf::RectangleShape empty(sf::Vector2f(size, size));

    wall.setFillColor(sf::Color::White);
    apple.setFillColor(sf::Color::Red);
    snake.setFillColor(sf::Color::Green);
    empty.setFillColor(sf::Color::Black);

    for (auto &currentWall : _wall) {
        wall.setPosition(currentWall.first * size, currentWall.second * size);
        window->draw(wall);
    }
    for (auto &currentApple : _apple) {
        apple.setPosition(currentApple.first * size, currentApple.second * size);
        window->draw(apple);
    }
    for (auto &currentSnake : _snake) {
        snake.setPosition(currentSnake.first * size, currentSnake.second * size);
        window->draw(snake);
    }
    for (auto &currentEmpty : _empty) {
        empty.setPosition(currentEmpty.first * size, currentEmpty.second * size);
        window->draw(empty);
    }
    DrawText({{"Best Score : " + std::to_string(best_score), {450, 100}}}, 24);
    DrawText({{"Score : " + std::to_string(score), {450, 200}}}, 24);
}

void sfml::DrawText(std::vector<Arcade::text_t> text, int size)
{
    sf::Font font;
    if (!font.loadFromFile("Assets/arial.ttf")) {
        std::cerr << "Failed to load font from file 'Assets/arial.ttf'" << std::endl;
        return;
    }

    for (auto &draw : text) {
        sf::Text sfText(draw.text, font);
        sfText.setCharacterSize(size);
        sfText.setFillColor(sf::Color::White);
        sfText.setPosition(draw.pos.x, draw.pos.y);
        window->draw(sfText);
    }
}

Arcade::Inputs sfml::Input() const
{
    sf::Event event;
    Arcade::Inputs interpretedKey = Arcade::Inputs::UNKNOWN;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return Arcade::Inputs::Q;
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::A:
                    interpretedKey = Arcade::Inputs::A;
                    break;
                case sf::Keyboard::B:
                    interpretedKey = Arcade::Inputs::B;
                    break;
                case sf::Keyboard::C:
                    interpretedKey = Arcade::Inputs::C;
                    break;
                case sf::Keyboard::D:
                    interpretedKey = Arcade::Inputs::D;
                    break;
                case sf::Keyboard::E:
                    interpretedKey = Arcade::Inputs::E;
                    break;
                case sf::Keyboard::F:
                    interpretedKey = Arcade::Inputs::F;
                    break;
                case sf::Keyboard::G:
                    interpretedKey = Arcade::Inputs::G;
                    break;
                case sf::Keyboard::H:
                    interpretedKey = Arcade::Inputs::H;
                    break;
                case sf::Keyboard::I:
                    interpretedKey = Arcade::Inputs::I;
                    break;
                case sf::Keyboard::J:
                    interpretedKey = Arcade::Inputs::J;
                    break;
                case sf::Keyboard::K:
                    interpretedKey = Arcade::Inputs::K;
                    break;
                case sf::Keyboard::L:
                    interpretedKey = Arcade::Inputs::L;
                    break;
                case sf::Keyboard::M:
                    interpretedKey = Arcade::Inputs::M;
                    break;
                case sf::Keyboard::N:
                    interpretedKey = Arcade::Inputs::N;
                    break;
                case sf::Keyboard::O:
                    interpretedKey = Arcade::Inputs::O;
                    break;
                case sf::Keyboard::P:
                    interpretedKey = Arcade::Inputs::P;
                    break;
                case sf::Keyboard::Q:
                    interpretedKey = Arcade::Inputs::Q;
                    break;
                case sf::Keyboard::R:
                    interpretedKey = Arcade::Inputs::R;
                    break;
                case sf::Keyboard::S:
                    interpretedKey = Arcade::Inputs::S;
                    break;
                case sf::Keyboard::T:
                    interpretedKey = Arcade::Inputs::T;
                    break;
                case sf::Keyboard::U:
                    interpretedKey = Arcade::Inputs::U;
                    break;
                case sf::Keyboard::V:
                    interpretedKey = Arcade::Inputs::V;
                    break;
                case sf::Keyboard::W:
                    interpretedKey = Arcade::Inputs::W;
                    break;
                case sf::Keyboard::X:
                    interpretedKey = Arcade::Inputs::X;
                    break;
                case sf::Keyboard::Y:
                    interpretedKey = Arcade::Inputs::Y;
                    break;
                case sf::Keyboard::Z:
                    interpretedKey = Arcade::Inputs::Z;
                    break;
                case sf::Keyboard::Up:
                    interpretedKey = Arcade::Inputs::UP;
                    break;
                case sf::Keyboard::Down:
                    interpretedKey = Arcade::Inputs::DOWN;
                    break;
                case sf::Keyboard::Escape:
                    interpretedKey = Arcade::Inputs::ESC;
                    break;
                case sf::Keyboard::Return:
                    interpretedKey = Arcade::Inputs::ENTER;
                    break;
                case sf::Keyboard::Space:
                    interpretedKey = Arcade::Inputs::SPACE;
                    break;
                default:
                    interpretedKey = Arcade::Inputs::UNKNOWN;
                    break;
            }
        }
    }
    return interpretedKey;
}

void sfml::DrawRectangles(const std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t color) {
    for (const auto& rect : rectangles) {
        sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
        shape.setPosition(rect.x, rect.y);
        shape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
        window->draw(shape);
    }
}

void sfml::LoadBackground(const std::string& imagePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(imagePath))
        throw ErrorFind(std::cerr, std::string("Failed to load background image from ") + imagePath);
    sf::Sprite background;
    background.setTexture(texture);
    background.setScale(
        static_cast<float>(window->getSize().x) / texture.getSize().x,
        static_cast<float>(window->getSize().y) / texture.getSize().y
    );
    window->draw(background);
    background = background;
}

void sfml::Sleep()
{
    sf::sleep(sf::milliseconds(100));
}
