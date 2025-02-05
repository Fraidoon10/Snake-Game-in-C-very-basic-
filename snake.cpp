#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
vector<pair<int, int>> snake;

void Setup() {
    gameOver = false;
    dir = RIGHT;
    x = width / 2;
    y = height / 2;
    snake.clear();
    snake.push_back(make_pair(x, y));
    snake.push_back(make_pair(x - 1, y));
    snake.push_back(make_pair(x - 2, y));
    score = 0;

    bool foodOnSnake;
    do {
        foodX = rand() % width;
        foodY = rand() % height;
        foodOnSnake = false;
        for (auto segment : snake) {
            if (foodX == segment.first && foodY == segment.second) {
                foodOnSnake = true;
                break;
            }
        }
    } while (foodOnSnake);
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            bool isSnake = false;
            for (auto segment : snake) {
                if (segment.first == j && segment.second == i) {
                    if (segment == snake[0])
                        cout << "O";
                    else
                        cout << "o";
                    isSnake = true;
                    break;
                }
            }
            if (!isSnake) {
                if (j == foodX && i == foodY)
                    cout << "@";
                else
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void Input() {
    if (_kbhit()) {
        int key = _getch();
        if (key == 224) { // Arrow key handling
            int dirKey = _getch();
            switch (dirKey) {
            case 72:
                if (dir != DOWN) dir = UP;
                break;
            case 80:
                if (dir != UP) dir = DOWN;
                break;
            case 75:
                if (dir != RIGHT) dir = LEFT;
                break;
            case 77:
                if (dir != LEFT) dir = RIGHT;
                break;
            }
        }
        else if (key == 'x' || key == 'X') {
            gameOver = true;
        }
    }
}

void Logic() {
    pair<int, int> new_head = snake[0];
    switch (dir) {
    case LEFT:  new_head.first--; break;
    case RIGHT: new_head.first++; break;
    case UP:    new_head.second--; break;
    case DOWN:  new_head.second++; break;
    }

    // Wall collision check
    if (new_head.first < 0 || new_head.first >= width || new_head.second < 0 || new_head.second >= height)
        gameOver = true;

    // Self collision check
    for (auto segment : snake)
        if (new_head == segment)
            gameOver = true;

    if (gameOver)
        return;

    bool ateFood = (new_head.first == foodX && new_head.second == foodY);
    if (ateFood) {
        score += 10;
        bool foodOnSnake;
        do {
            foodX = rand() % width;
            foodY = rand() % height;
            foodOnSnake = false;
            for (auto segment : snake) {
                if (foodX == segment.first && foodY == segment.second) {
                    foodOnSnake = true;
                    break;
                }
            }
        } while (foodOnSnake);
    }
    else {
        snake.pop_back();
    }

    snake.insert(snake.begin(), new_head);
}

int main() {
    srand(time(0));
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Adjust game speed by changing sleep duration
    }
    return 0;
}