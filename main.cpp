#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
using std::cout;
using std::endl;
using std::vector;

int height = 22, width = 22;
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

bool hitWall(const Position& head) {
    return (head.x == 0 || head.x == width-1
        || head.y == 0 || head.y == height-1);
}


Position spawnFruit(const vector<Position>& snake) {
    while (true) {
        Position fruit;
        fruit.x = rand() % width;
        fruit.y = rand() % height;

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
    Direction& nextDirection, Position& fruit, bool& gameOver) {
    if (!isOpposite(currentDirection, nextDirection)) {
        currentDirection = nextDirection;
    }
    bool ate = snakeEat(snake, fruit);

    updateSnake(snake, currentDirection, ate);

    if (ate) {
        fruit = spawnFruit(snake);
    }
    if (hitSelf(snake)) {
        gameOver = true;
    }
    if (hitWall(snake[0])) {
        gameOver = true;
    }
}

//Makes snake appear
void Draw(const vector<Position>& snake, const Position& fruit) {
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
                        cout << (i ==0 ? "S" : "s");
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

    for (const Position& s : snake) {
        cout << "(" << s.x << "," << s.y << ") ";
    }
    cout << endl;
}


int main(){
    vector<Position> snake = {
        {11,11},{10,11},{9,11}
    };
    Position fruit = {13, 11};

    Direction currentDirection = RIGHT;
    Direction nextDirection = RIGHT;

    bool gameOver = false;

    srand(time(0));

    while (!gameOver) {
        for (int i = 0; i <10; i++) {
            Input(nextDirection);
            Logic(snake, currentDirection, nextDirection, fruit, gameOver);
            Draw(snake,fruit);
            Sleep(100);
        }
        gameOver = true;
    }
    return 0;

}
