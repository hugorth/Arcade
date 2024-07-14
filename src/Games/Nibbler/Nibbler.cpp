/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** nibbler
*/

#include "../../../include/Games/Nibbler.hpp"

void nibbler::addWalls(int startX, int endX, int startY, int endY, int incrementX, int incrementY) {
    for (int x = startX; x <= endX; x += incrementX) {
        for (int y = startY; y <= endY; y += incrementY) {
            walls.push_back({x, y});
        }
    }
}

void nibbler::saveHighScore() {
    std::ofstream file("Assets/highscore_nibbler.txt");
    if (file.is_open()) {
        file << score;
        file.close();
    } else {
        std::cout << "Unable to open file";
    }
}

bool nibbler::isBestScore() {
    std::ifstream file("Assets/highscore_nibbler.txt");
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

void nibbler::generateFruit() {
    while (true) {
        fruit.x = 2 + (rand() % static_cast<int>(width - 2));
        fruit.y = 2 + (rand() % static_cast<int>(height - 2));

        bool isInsideWall = false;
        for (auto& w : walls) {
            if (w.x == fruit.x && w.y == fruit.y) {
                isInsideWall = true;
                break;
            }
        }

        if (!isInsideWall) {
            break;
        }
    }
}

nibbler::nibbler() : IGameModule() {
    srand(time(0));
    x = width / 2;
    y = height / 2;
    for (int i = 0; i < 4; ++i) {
        tail.push_front({x, y});
    }
    
    addWalls(2, 2, 2, 5, 1, 1);
    addWalls(18, 18, 2, 5, 1, 1);
    addWalls(5, 5, 2, 8, 1, 1);
    addWalls(15, 15, 2, 8, 1, 1);
    addWalls(2, 2, 15, 18, 1, 1);
    addWalls(18, 18, 15, 18, 1, 1);

    addWalls(2, 18, 1, 1, 1, 1);
    addWalls(7, 13, 13, 13, 1, 1);
    addWalls(9, 11, 14, 14, 1, 1);
    addWalls(4, 16, 15, 15, 1, 1);
    addWalls(2, 18, 18, 18, 1, 1);

    generateFruit();
}

void nibbler::Logic() {
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

    if (next.x < 1 || next.x >= width || next.y < 0 || next.y >= height || isWall(next.x, next.y)) {
        switch (dir) {
            case Direction::UP:
                dir = Direction::RIGHT;
                break;
            case Direction::DOWN:
                dir = Direction::LEFT;
                break;
            case Direction::LEFT:
                dir = Direction::UP;
                break;
            case Direction::RIGHT:
                dir = Direction::DOWN;
                break;
        }
    } else {
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
                generateFruit();
            } else {
                tail.pop_back();
            }
            x = next.x;
            y = next.y;
        }
    }
    if (gameOver) {
        RestartGame();
        gameOver = false;
    }
}

int nibbler::getHighScore() {
    std::ifstream file("Assets/highscore_nibbler.txt");
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

void nibbler::Draw(Arcade::IDisplayModule &display) {
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
                for (auto& w : walls) {
                    if (w.x == j && w.y == i) {
                            _wall.push_back(std::make_pair(j, (i + 1)));
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

void nibbler::RestartGame() {
    score = 0;
    tail.clear();
    x = width / 2;
    y = height / 2;
    for (int i = 0; i < 4; ++i) {
        tail.push_front({x, y});
    }
}

void nibbler::Input(Arcade::Inputs input) {
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
    return new nibbler();
}