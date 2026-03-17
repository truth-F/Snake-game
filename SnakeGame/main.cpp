#include <iostream>
#include  <conio.h>
#include <vector>
using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };
struct Position {
    int x;
    int y;
};
Position move(Position current, Direction d) {
    Position newPos = current;

    switch (d) {
        case UP:
            newPos.y +=1;
            break;
        case DOWN:
            newPos.y -=1;
            break;
        case RIGHT:
            newPos.x +=1;
            break;
        case LEFT:
            newPos.x -=1;
            break;
    }
    return newPos;
}



int main() {
    Position head = {5,5};
    cout << head.x << " " << head.y << endl;
    head = move(head, DOWN);
    cout << head.x << " " << head.y << endl;
    head = move(head, RIGHT);
    cout << head.x << " " << head.y << endl;

    return 0;
}