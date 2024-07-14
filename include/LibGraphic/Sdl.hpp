/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sdl
*/

#ifndef SDL_HPP_
    #define SDL_HPP_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <memory>
    #include "../Core/IDisplayModule.hpp"
    #include "../Core/Error_find.hpp"

struct SDL_WindowDeleter {
    void operator()(SDL_Window* window) const {
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
};

struct SDL_RendererDeleter {
    void operator()(SDL_Renderer* renderer) const {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
    }
};

class sdl : public Arcade::IDisplayModule
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font *font;
    SDL_Surface *surface;
    SDL_Texture *texture;

    public:
        sdl();

        void Init(const char* title, size_t width, size_t height, Uint32 flags);
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

        ~sdl();
};

#endif /* !SDL_HPP_ */
