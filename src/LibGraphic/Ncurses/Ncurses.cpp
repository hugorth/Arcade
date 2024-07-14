/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ncurse
*/

#include "../../../include/LibGraphic/Ncurses.hpp"
#include "../../../include/Core/Core.hpp"
#include <fstream>
#include <unistd.h>

extern "C" Arcade::IDisplayModule *Lib()
{
    return new ncurse();
}

void ncurse::Screen()
{
    screen = newterm(NULL, stdin, stdout);
    set_term(screen);
}

void ncurse::InitializeWindow(size_t width, size_t height)
{
    window = newwin(height / 10, width / 10, 0, 0);
    keypad(window, TRUE);
    nodelay(window, TRUE);
}

void ncurse::SetWindowProperties()
{
    noecho();
    curs_set(0);
}

void ncurse::Window(size_t width, size_t height)
{
    Screen();
    InitializeWindow(width, height);
    SetWindowProperties();
}

void ncurse::Update()
{
    wrefresh(window);
}

void ncurse::Clear(bool menu)
{
    werase(window);
    if (menu)
        box(window, 0, 0);
}

void ncurse::LoadBackground(const std::string& imagePath) {
}

int ncurse::ConvertColorToPair(Arcade::color_t color) {
    return color.r + color.g + color.b + color.a;
}

void ncurse::DrawRectangles(const std::vector<Arcade::rectangle_t>& rectangles, Arcade::color_t color) {
    mvwprintw(window, 400, 400, "->");
}

void ncurse::Destroy()
{
    echo();
    nodelay(window, FALSE);
    keypad(window, FALSE);
    delwin(window);
    endwin();
    delscreen(screen);
}


void ncurse::Draw(std::vector<std::pair<int, int>> _wall, std::vector<std::pair<int, int>> _apple, std::vector<std::pair<int, int>> _snake, std::vector<std::pair<int, int>> _empty, int score, int best_score)
{
    for (auto &currentWall : _wall) {
        mvwprintw(window, currentWall.second, currentWall.first, "#");
    }
    for (auto &currentApple : _apple) {
        mvwprintw(window, currentApple.second, currentApple.first, "*");
    }
    for (auto &currentSnake : _snake) {
        mvwprintw(window, currentSnake.second, currentSnake.first, "O");
    }
    for (auto &currentEmpty : _empty) {
        mvwprintw(window, currentEmpty.second, currentEmpty.first, " ");
    }
    DrawText({{"Best Score : " + std::to_string(best_score), {900, 100}}}, 24);
    DrawText({{"Score : " + std::to_string(score), {900, 200}}}, 24);
}

void ncurse::DrawText(std::vector<Arcade::text_t> text, int size)
{
    if (!this->window) {
        std::cerr << "Window pointer is null. Cannot draw text." << std::endl;
        return;
    }

    for (const auto& draw : text) {
        if (!draw.text.empty()) {
            mvwprintw(window, draw.pos.y / 40, draw.pos.x / 40, "%s", draw.text.c_str());
        }
    }
}

Arcade::Inputs ncurse::Input() const
{
    int Inputs = wgetch(window);

    switch (Inputs) {
        case 'a': return Arcade::Inputs::A;
        case 'b': return Arcade::Inputs::B;
        case 'c': return Arcade::Inputs::C;
        case 'd': return Arcade::Inputs::D;
        case 'e': return Arcade::Inputs::E;
        case 'f': return Arcade::Inputs::F;
        case 'g': return Arcade::Inputs::G;
        case 'h': return Arcade::Inputs::H;
        case 'i': return Arcade::Inputs::I;
        case 'j': return Arcade::Inputs::J;
        case 'k': return Arcade::Inputs::K;
        case 'l': return Arcade::Inputs::L;
        case 'm': return Arcade::Inputs::M;
        case 'n': return Arcade::Inputs::N;
        case 'o': return Arcade::Inputs::O;
        case 'p': return Arcade::Inputs::P;
        case 'q': return Arcade::Inputs::Q;
        case 'r': return Arcade::Inputs::R;
        case 's': return Arcade::Inputs::S;
        case 't': return Arcade::Inputs::T;
        case 'u': return Arcade::Inputs::U;
        case 'v': return Arcade::Inputs::V;
        case 'w': return Arcade::Inputs::W;
        case 'x': return Arcade::Inputs::X;
        case 'y': return Arcade::Inputs::Y;
        case 'z': return Arcade::Inputs::Z;
        case ' ': return Arcade::Inputs::SPACE;
        case 259: return Arcade::Inputs::UP;
        case 258: return Arcade::Inputs::DOWN;
        case 27: return Arcade::Inputs::ESC;
        case 10: return Arcade::Inputs::ENTER;
        default: return Arcade::Inputs::UNKNOWN;
    }
}

void ncurse::Sleep()
{
    usleep(100000);
}

ncurse::~ncurse()
{
    delwin(window);
    endwin();
    delscreen(screen);
}
