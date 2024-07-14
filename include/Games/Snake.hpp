/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** snake
*/

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

    #include "../Core/IGameModule.hpp"

class snake : public Arcade::IGameModule {
    protected:
public :
    snake();
    void getLogic() {   
        return (Logic());
    }
    void Logic() override;
    void Draw(Arcade::IDisplayModule &display) override;
    void Input(Arcade::Inputs input) override;
    void RestartGame() override;
    void saveHighScore() override;
    bool isBestScore() override;
    int getHighScore() override;
private:
};

#endif /* !SNAKE_HPP_ */