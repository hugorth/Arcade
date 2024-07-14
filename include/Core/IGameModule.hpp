/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGameModule.hpp
*/

#ifndef IGameModule_HPP_
    #define IGameModule_HPP_

#include <iostream>
#include <thread>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "IDisplayModule.hpp"

enum class Direction {UP, DOWN, LEFT, RIGHT, STOP};

struct Position {
    int x;
    int y;
};

struct Wall {
    int x, y;
};

namespace Arcade {
    class IGameModule {
    public:
        bool gameOver;
        Direction dir;
        int x, y;
        int score;
        int speed;
        Position fruit;
        std::deque<Position> tail;
        std::vector<Wall> walls;

        static const int width = 20;
        static const int height = 20;

        std::vector<std::pair<int, int>> _snake;
         std::vector<std::pair<int, int>> _apple;
        std::vector<std::pair<int, int>> _wall;
        std::vector<std::pair<int, int>> _empty;

        IGameModule() : gameOver(false), dir(Direction::UP), x(width/2), y(height/2 + 4), score(0), speed(100) {};
        virtual ~IGameModule() = default;
        virtual void Input(Arcade::Inputs input) = 0;
        virtual void Draw(Arcade::IDisplayModule &display) = 0;
        virtual void Logic() = 0;
        virtual void RestartGame() = 0;
        virtual void saveHighScore() = 0;
        virtual bool isBestScore() = 0;
        virtual int getHighScore() = 0;

    private:
    };
};

#endif /* IGameModule_HPP_*/
