#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WIDTH = 50;
const int HEIGHT = 25;
const int INITIAL_LENGTH = 4;

vector<pair<int, int>> snake;
pair<int, int> food;
int direction;
bool gameOver;
int score;

enum Dir { STOP = 0, LEFT, RIGHT, UP, DOWN };

// Set console text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Set cursor position
void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Game setup
void setup() {
    gameOver = false;
    direction = RIGHT; // Initial direction is RIGHT
    score = 0;

    snake.clear();
    // Fix: Initialize the snake so the head is at the right end
    for (int i = 0; i < INITIAL_LENGTH; i++)
        snake.push_back({WIDTH / 2 - i, HEIGHT / 2});

    food.first = rand() % (WIDTH - 2) + 1; // Random food position
    food.second = rand() % (HEIGHT - 2) + 1;
}

// Draw game elements
void draw() {
    system("cls");
    
    // Debug output
    cout << "Direction: " << direction << endl;
    cout << "Snake Head: (" << snake[0].first << ", " << snake[0].second << ")" << endl;
    cout << "Food: (" << food.first << ", " << food.second << ")" << endl;

    // Draw top border
    setColor(11); // cyan
    for(int i = 0; i < WIDTH; i++)
        cout << "#";
    cout << endl;

    for(int y = 1; y < HEIGHT-1; y++) {
        for(int x = 0; x < WIDTH; x++) {
            if(x == 0 || x == WIDTH-1) {
                setColor(11);
                cout << "#";
            }
            else if(x == food.first && y == food.second) {
                setColor(12); // red
                cout << "¤";
            }
            else {
                bool isSnake = false;
                for(int i = 0; i < snake.size(); i++) {
                    if(snake[i].first == x && snake[i].second == y) {
                        setColor(i == 0 ? 10 : 2); // head: bright green, body: green
                        cout << (i == 0 ? "Ø" : "ø");
                        isSnake = true;
                        break;
                    }
                }
                if(!isSnake) cout << " ";
            }
        }
        cout << endl;
    }

    // Draw bottom border
    setColor(11);
    for(int i = 0; i < WIDTH; i++)
        cout << "#";
    cout << endl;

    setColor(15); // white
    cout << "Score: " << score << endl;
}

// Input handling
void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 75: // left arrow
                if (direction != RIGHT) direction = LEFT;
                break;
            case 77: // right arrow
                if (direction != LEFT) direction = RIGHT;
                break;
            case 72: // up arrow
                if (direction != DOWN) direction = UP;
                break;
            case 80: // down arrow
                if (direction != UP) direction = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

// Game logic
void logic() {
    if (direction == STOP) return;

    pair<int, int> newHead = snake[0];

    switch (direction) {
        case LEFT:  newHead.first--; break;
        case RIGHT: newHead.first++; break;
        case UP:    newHead.second--; break;
        case DOWN:  newHead.second++; break;
    }

    // Debug output
    cout << "New Head: (" << newHead.first << ", " << newHead.second << ")" << endl;

    // Wall collision check
    if (newHead.first <= 0 || newHead.first >= WIDTH - 1 ||
        newHead.second <= 0 || newHead.second >= HEIGHT - 1) {
        gameOver = true;
        cout << "Wall collision detected!" << endl;
    }

    // Self collision check
    for (int i = 1; i < snake.size(); i++) {
        if (snake[i] == newHead) {
            gameOver = true;
            cout << "Self collision detected!" << endl;
        }
    }

    // Food collection
    if (newHead == food) {
        score += 10;
        food.first = rand() % (WIDTH - 2) + 1;
        food.second = rand() % (HEIGHT - 2) + 1;
    } else {
        snake.pop_back();
    }

    snake.insert(snake.begin(), newHead);
}

int main() {
    srand(time(0));
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(500); // Adjust game speed for debugging
    }

    setColor(12);
    gotoXY(WIDTH / 2 - 5, HEIGHT / 2);
    cout << "GAME OVER!";
    gotoXY(WIDTH / 2 - 6, HEIGHT / 2 + 1);
    cout << "Final Score: " << score;
    gotoXY(0, HEIGHT + 2);

    // Wait for user input before closing
    cout << "\nPress any key to exit...";
    _getch();

    return 0;
}
