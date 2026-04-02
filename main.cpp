#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
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
Position move(Position snakeCurrent, Direction d) {
    Position newPos = snakeCurrent;
    switch (d) {
        case RIGHT: newPos.x +=1; break;
        case LEFT:  newPos.x -=1; break;
        case UP:    newPos.y +=1; break;
        case DOWN:  newPos.y -=1; break;
    }
    return newPos;
}

bool snakeEat(const vector<Position>& snake, const Position currentFruit) {
    return((snake[0].x == currentFruit.x) && (snake[0].y == currentFruit.y));
}


bool hitSelf(const vector<Position>& snake) {
    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }
    return false;
}

bool hitWall(const Position& head, int height, int width) {
    return (head.x == 0 || head.x == width-1
        || head.y == 0 || head.y == height-1);
}


Position spawnFruit(const vector<Position>& snake, int height, int width) {
    while (true) {
        Position fruit;
        fruit.x = rand() % (width - 2) + 1;
        fruit.y = rand() % (height - 2) + 1;

        bool available = true;

        for (const Position& s : snake) {
            if (s.x == fruit.x && s.y == fruit.y) {
                available = false;
                break;
            }
        }
        if (available) {
            return fruit;
        }
    }
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
void updateSnake(vector<Position>& snake, Direction dir, bool grow) {
    Position newHead = move(snake[0], dir);

    snake.insert(snake.begin(), newHead);

    if (!grow) {
        snake.pop_back();
    }
}


//Defines rules for snake
void Logic(vector<Position>& snake, Direction& currentDirection,
    Direction& nextDirection, Position& fruit, int height, int width, int& score, bool& gameOver) {
    if (!isOpposite(currentDirection, nextDirection)) {
        currentDirection = nextDirection;
    }
    bool ate = snakeEat(snake, fruit);

    updateSnake(snake, currentDirection, ate);

    if (ate) {
        score++;
        fruit = spawnFruit(snake, height, width);
    }
    if (hitSelf(snake)) {
        gameOver = true;
    }
    if (hitWall(snake[0], height, width)) {
        gameOver = true;
    }
}

//Makes snake appear
void Draw(const vector<Position>& snake, const Position& fruit,
            int height, int width, int score, bool gameOver) {

    system("cls");

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Draw the top/bottom and side walls
            if (y == 0 ||y  == height-1 || x == 0 || x == width-1) {
                cout << "#";
            }else {
                bool printed = false;

                for (size_t i = 0; i < snake.size(); i++) {
                    if (snake[i].x == x && snake[i].y == y) {
                        cout << (i == 0 ? "S" : "s");
                        printed = true;
                        break;
                    }
                }
                if (!printed) {
                    if (fruit.x == x && fruit.y == y) {
                        cout << "o";
                    } else {
                        cout << " ";
                    }
                }
            }
        }
        cout << endl; // Move to the next row
    }
    cout << "Score: " << score << endl;
}

void DrawGameOver(int height, int width, int score) {
    COORD coord;

    system("cls");

    int centerX = width / 2;
    int centerY = height / 2;

    coord.X = 0;
    coord.Y = centerY - 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << endl << " ===== GAME OVER ===== ";

    coord.X = centerX - 8;
    coord.Y = centerY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "Final Score: " << score << endl
        << "Press any key to exit...";

    _getch();

}


int main(){
    int height = 12, width = 22;

    vector<Position> snake = {
        {11,5},{10,5},{9,5}
    };
    Position fruit = {15, 5};

    Direction currentDirection = RIGHT;
    Direction nextDirection = RIGHT;

    int delay = 120;
    int score = 0;

    bool gameOver = false;

    srand(time(0));

    //Test DO NOT PRESS INFINITE LOOP
    while (!gameOver) {
        Input(nextDirection);
        Logic(snake, currentDirection, nextDirection, fruit, height, width, score, gameOver);
        Draw(snake, fruit, height, width, score, gameOver);
        Sleep(delay);
    }

    DrawGameOver(height, width, score);
    return 0;

}