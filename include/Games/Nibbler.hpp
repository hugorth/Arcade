/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
    #define NIBBLER_HPP_

    #include "../Core/IGameModule.hpp"
    #include "../Core/IDisplayModule.hpp"
    #include <fstream>
    #include <map>

class nibbler : public Arcade::IGameModule {
protected:
public:
    nibbler();
    void getLogic() {   
        return (Logic());
    }
    void Draw(Arcade::IDisplayModule &display) override;
    void Input(Arcade::Inputs input) override;
    void Logic() override;
    void RestartGame() override;
    void saveHighScore() override;
    bool isBestScore() override;
    int getHighScore() override;
    void addWalls(int startX, int endX, int startY, int endY, int incrementX, int incrementY);
    void generateFruit();
    bool isWall(int x, int y) {
        for (auto& w : walls) {
            if (w.x == x && w.y == y) {
                return true;
            }
        }
        return false;
    }
private:
};

#endif /* !NIBBLER_HPP_ */