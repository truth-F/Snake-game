#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

//Basic direction & position
enum Direction { UP, DOWN, LEFT, RIGHT };
struct Position {
    int x;
    int y;
};

//Is snake turning into itself?
bool isOpposite(Direction a, Direction b) {
    return (a == UP && b == DOWN)||
           (a == DOWN && b == UP)||
           (a == RIGHT && b == LEFT)||
           (a == LEFT && b == RIGHT);
}

//Movement based on direction
Position move(Position current, Direction d) {
    Position newPos = current;
    switch (d) {
        case RIGHT: newPos.x +=1; break;
        case LEFT:  newPos.x -=1; break;
        case UP:    newPos.y +=1; break;
        case DOWN:  newPos.y -=1; break;
    }
    return newPos;
}

//Process real-time user input
void Input(Direction& nextDirection) {
    if (_kbhit()) {
        char key = _getch();

        switch (key) {
            case 'w': nextDirection = UP; break;
            case 's': nextDirection = DOWN; break;
            case 'a': nextDirection = LEFT; break;
            case 'd': nextDirection = RIGHT; break;
        }
    }
}

//Moves snake
void moveSnake(vector<Position>& snake, Direction dir) {
    Position newHead = move(snake[0], dir);

    for (size_t i = snake.size() -1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    snake[0] = newHead;
}


//Defines rules for snake
void Logic(vector<Position>& snake, Direction& currentDirection, Direction& nextDirection) {
    if (!isOpposite(currentDirection, nextDirection)) {
        currentDirection = nextDirection;
    }

    moveSnake(snake, currentDirection);
}

//Makes snake appear
void Draw(const vector<Position>& snake) {
    system("cls");

    for (const Position& o : snake) {
        cout << "(" << o.x << "," << o.y << ") ";
    }
    cout << endl;
}


int main(){
    vector<Position> snake = {
        {5,5},{4,5},{3,5}
    };

    Direction currentDirection = RIGHT;
    Direction nextDirection = RIGHT;

    //Test DO NOT PRESS INFINIT LOOP
    while (true) {
        Input(nextDirection);
        Logic(snake, currentDirection, nextDirection);
        Draw(snake);
        Sleep(100);
    }


    return 0;

}