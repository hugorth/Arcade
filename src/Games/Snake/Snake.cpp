/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** snake
*/

#include "../../../include/Games/Snake.hpp"

snake::snake() : IGameModule() {
    srand(time(0));
    fruit.x = 2 + (rand() % static_cast<int>(width - 2));
    fruit.y = 2 + (rand() % static_cast<int>(height - 2));
    x = width / 2;
    y = height / 2;
    for (int i = 0; i < 4; ++i) {
        tail.push_front({x, y});
    }
}

#include <fstream>

void snake::saveHighScore() {
    std::ofstream file("Assets/highscore_snake.txt");
    if (file.is_open()) {
        file << score;
        file.close();
    } else {
        std::cout << "Unable to open file";
    }
}

bool snake::isBestScore() {
    std::ifstream file("Assets/highscore_snake.txt");
    if (file.is_open()) {
        std::string line;
        if (getline(file, line)) {
            int highScore = std::stoi(line);
            file.close();
            return score > highScore;
        }
        file.close();
    } else {
        std::cout << "Unable to open file";
    }
    return false;
}

int snake::getHighScore() {
    std::ifstream file("Assets/highscore_snake.txt");
    if (file.is_open()) {
        std::string line;
        if (getline(file, line)) {
            int highScore = std::stoi(line);
            file.close();
            return highScore;
        }
        file.close();
    } else {
        std::cout << "Unable to open file";
    }
    return 0;
}

void snake::Logic() {
    Position next = {x, y};

    switch (dir) {
        case Direction::UP:
            next.y--;
            break;
        case Direction::DOWN:
            next.y++;
            break;
        case Direction::LEFT:
            next.x--;
            break;
        case Direction::RIGHT:
            next.x++;
            break;
    }

    if (next.x < 1 || next.x >= width || next.y < 0 || next.y >= height)
        gameOver = true;

    for (auto& t : tail)
        if (t.x == next.x && t.y == next.y)
            gameOver = true;

    if (!gameOver) {
        if (isBestScore())
                saveHighScore();
        tail.push_front(next);
        if (next.x == fruit.x && next.y == fruit.y) {
            score += 10;
            speed = std::max(10, speed - 1);
            fruit.x = rand() % width;
            fruit.y = rand() % height;
        } else {
            tail.pop_back();
        }
        x = next.x;
        y = next.y;
    }
    if (gameOver) {
        RestartGame();
        gameOver = false;
    }
}

void snake::Draw(Arcade::IDisplayModule &display) {
    int best_score = getHighScore();
    _snake.clear();
    _apple.clear();
    for (int i = 0; i < width + 1; i++) {
        _wall.push_back(std::make_pair(i, 0));
    }
    int i = 0;

    while (i < height) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                _wall.push_back(std::make_pair(j, (i + 1)));
            } else if (i == y && j == x) {
                _snake.push_back(std::make_pair(j, (i + 1)));
            } else if (i == fruit.y && j == fruit.x) {
                _apple.push_back(std::make_pair(j, (i + 1)));
            } else {
                bool print = false;
                for (auto& t : tail) {
                    if (t.x == j && t.y == i) {
                        _snake.push_back(std::make_pair(j, (i + 1)));
                        print = true;
                    }
                }
            }
            if (j == width - 1) {
                _wall.push_back(std::make_pair((j + 1), (i + 1)));
            }
        }
        i++;
    }

    for (int count = 0; count < width + 1; count++)
        _wall.push_back(std::make_pair(count, (i + 1)));

    display.Draw(_wall, _apple, _snake, _empty, score, best_score);
}

void snake::RestartGame() {
    score = 0;
    tail.clear();
    x = width / 2;
    y = height / 2;
    for (int i = 0; i < 4; ++i) {
        tail.push_front({x, y});
    }
}

void snake::Input(Arcade::Inputs input) {
    switch (input) {
        case Arcade::Inputs::Z:
            dir = Direction::UP;
            break;
        case Arcade::Inputs::S:
            dir = Direction::DOWN;
            break;
        case Arcade::Inputs::Q:
            dir = Direction::LEFT;
            break;
        case Arcade::Inputs::D:
            dir = Direction::RIGHT;
            break;
        case Arcade::Inputs::A:
            break;
        case Arcade::Inputs::SPACE:
            speed = std::max(10, speed - 5);
            break;
        case Arcade::Inputs::R:
            RestartGame();
            break;
    }
}

extern "C" Arcade::IGameModule *Game()
{
    return new snake();
}
