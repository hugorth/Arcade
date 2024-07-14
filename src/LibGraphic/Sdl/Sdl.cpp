/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sdl
*/

#include "../../../include/LibGraphic/Sdl.hpp"
#include "../../../include/Core/IGameModule.hpp"

struct SDL_SurfaceDeleter {
    void operator()(SDL_Surface* surface) const {
        if (surface) {
            SDL_FreeSurface(surface);
        }
    }
};

extern "C" Arcade::IDisplayModule *Lib() {
    return new sdl();
}

sdl::sdl() {
    TTF_Init();
    font = TTF_OpenFont("Assets/arial.ttf", 24);
}

void sdl::Init(const char* title, size_t width, size_t height, Uint32 flags) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    renderer = SDL_CreateRenderer(this->window, -1, 0);
}

void sdl::Window(size_t width, size_t height) {
    Init(NULL, width, height, SDL_WINDOW_RESIZABLE);
}

void sdl::Update() {
    SDL_RenderPresent(renderer);
}

void sdl::Clear(bool menu) {
    SDL_RenderClear(renderer);
}

void sdl::Destroy() {
    if (this->renderer) {
        renderer;
    }
    if (this->window) {
        window;
    }
}

void sdl::Draw(std::vector<std::pair<int, int>> _wall, std::vector<std::pair<int, int>> _apple, std::vector<std::pair<int, int>> _snake, std::vector<std::pair<int, int>> _empty, int score, int best_score) {
    int size = 25;
    SDL_Rect wall = {0, 0, size, size};
    SDL_Rect apple = {0, 0, size, size};
    SDL_Rect snake = {0, 0, size, size};
    SDL_Rect empty = {0, 0, size, size};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (auto &currentWall : _wall) {
        wall.x = currentWall.first * size;
        wall.y = currentWall.second * size;
        SDL_RenderFillRect(renderer, &wall);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (auto &currentApple : _apple) {
        apple.x = currentApple.first * size;
        apple.y = currentApple.second * size;
        SDL_RenderFillRect(renderer, &apple);
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (auto &currentSnake : _snake) {
        snake.x = currentSnake.first * size;
        snake.y = currentSnake.second * size;
        SDL_RenderFillRect(renderer, &snake);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (auto &currentEmpty : _empty) {
        empty.x = currentEmpty.first * size;
        empty.y = currentEmpty.second * size;
        SDL_RenderFillRect(renderer, &empty);
    }
    DrawText({{"Best Score : " + std::to_string(best_score), {600, 100}}}, 24);
    DrawText({{"Score : " + std::to_string(score), {600, 200}}}, 24);
}

void sdl::DrawText(std::vector<Arcade::text_t> text, int size) {
    for (auto &currentText : text) {
        SDL_Color color = {255, 255, 255, 255};
        surface = TTF_RenderText_Solid(font, currentText.text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = { static_cast<int>(currentText.pos.x), static_cast<int>(currentText.pos.y), surface->w, surface->h };
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        //SDL_DestroyTexture(texture);  // Properly destroy the texture
        //SDL_FreeSurface(surface);     // Properly free the surface
        if (surface != nullptr) {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
}

Arcade::Inputs sdl::Input() const {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return Arcade::Inputs::Q;
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_a: return Arcade::Inputs::A;
                case SDLK_b: return Arcade::Inputs::B;
                case SDLK_c: return Arcade::Inputs::C;
                case SDLK_d: return Arcade::Inputs::D;
                case SDLK_e: return Arcade::Inputs::E;
                case SDLK_f: return Arcade::Inputs::F;
                case SDLK_g: return Arcade::Inputs::G;
                case SDLK_h: return Arcade::Inputs::H;
                case SDLK_i: return Arcade::Inputs::I;
                case SDLK_j: return Arcade::Inputs::J;
                case SDLK_k: return Arcade::Inputs::K;
                case SDLK_l: return Arcade::Inputs::L;
                case SDLK_m: return Arcade::Inputs::M;
                case SDLK_n: return Arcade::Inputs::N;
                case SDLK_o: return Arcade::Inputs::O;
                case SDLK_p: return Arcade::Inputs::P;
                case SDLK_q: return Arcade::Inputs::Q;
                case SDLK_r: return Arcade::Inputs::R;
                case SDLK_s: return Arcade::Inputs::S;
                case SDLK_t: return Arcade::Inputs::T;
                case SDLK_u: return Arcade::Inputs::U;
                case SDLK_v: return Arcade::Inputs::V;
                case SDLK_w: return Arcade::Inputs::W;
                case SDLK_x: return Arcade::Inputs::X;
                case SDLK_y: return Arcade::Inputs::Y;
                case SDLK_z: return Arcade::Inputs::Z;
                case SDLK_SPACE: return Arcade::Inputs::SPACE;
                case SDLK_UP: return Arcade::Inputs::UP;
                case SDLK_DOWN: return Arcade::Inputs::DOWN;
                case SDLK_ESCAPE: return Arcade::Inputs::ESC;
                case SDLK_RETURN: return Arcade::Inputs::ENTER;
                default: return Arcade::Inputs::UNKNOWN;
            }
        }
    }
    return Arcade::Inputs::UNKNOWN;
}

void sdl::DrawRectangles(const std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (const auto& rect : rectangles) {
        SDL_Rect sdlRect = {rect.x, rect.y, rect.width, rect.height};
        SDL_RenderFillRect(renderer, &sdlRect);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void sdl::LoadBackground(const std::string& imagePath) {
    SDL_Surface* imageSurface = IMG_Load(imagePath.c_str());
    if (!imageSurface)
        throw ErrorFind(std::cerr, std::string("Failed to load image: ") + IMG_GetError());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (!texture) {
        SDL_FreeSurface(imageSurface);
        throw ErrorFind(std::cerr, std::string("Failed to create texture: ") + SDL_GetError());
    }

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    if (imageSurface != nullptr) {
        SDL_FreeSurface(imageSurface);
        imageSurface = nullptr;
    }
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    //SDL_DestroyTexture(texture);  // Properly destroy the texture
    //SDL_FreeSurface(imageSurface); // Properly free the surface
}

void sdl::Sleep() {
    SDL_Delay(100);
}

sdl::~sdl() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (surface != nullptr) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
