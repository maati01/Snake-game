//
// Created by mateu on 21.06.2022.
//

#ifndef SNAKE_GAME_SNAKE_H
#define SNAKE_GAME_SNAKE_H


class Snake {
public:
    struct Point {
        int x = 0;
        int y = 0;
    } p[100];

    Snake() = default;

    int getSnakeSize() const { return snakeSize; }

    void setSnakeSize(int size) { snakeSize = size; }

private:
    int snakeSize = 1;
};


#endif //SNAKE_GAME_SNAKE_H
