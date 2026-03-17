#include <iostream>
#include  <conio.h>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

enum Direction { UP, DOWN, LEFT, RIGHT };
struct Position {
    int x;
    int y;
};

bool isOpposite(Direction a, Direction b) {
    return (a == UP && b == DOWN)||
           (a == DOWN && b == UP)||
           (a == RIGHT && b == LEFT)||
           (a == LEFT && b == RIGHT);
}

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

int main(){
    vector<Position> snake = {
        {5,5},
        {4,5},
        {3,5}
    };
    Position head = snake[0];
    Position prev = snake[1];
    Direction currentDirection = RIGHT;
    Direction nextDirection = UP;
    cout << head.x << " " << head.y << endl;

    if (!isOpposite(currentDirection, nextDirection)) {
        currentDirection = nextDirection;
    }
    head = move(head, currentDirection);
    cout << head.x << " " << head.y << endl;


    return 0;

}