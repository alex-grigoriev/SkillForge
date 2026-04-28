#include <iostream>
using namespace std;

const int SIZE = 12;

// Инициализация (все пузырьки целые)
void init(bool bubble[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            bubble[i][j] = true;
}

// Отображение пупырки
void print(bool bubble[SIZE][SIZE]) {
    cout << "\nCurrent state:\n";

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (bubble[i][j])
                cout << "o ";
            else
                cout << "x ";
        }
        cout << endl;
    }
}

// Проверка координат
bool isValid(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

// Лопание региона
void popRegion(bool bubble[SIZE][SIZE], int x1, int y1, int x2, int y2) {
    // нормализация координат
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);

    // проверка
    if (!isValid(x1, y1) || !isValid(x2, y2)) {
        cout << "Invalid coordinates!\n";
        return;
    }

    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            if (bubble[i][j]) {
                bubble[i][j] = false;
                cout << "Pop!\n";
            }
        }
    }
}

// Проверка: остались ли целые
bool hasBubbles(bool bubble[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (bubble[i][j])
                return true;
    return false;
}

int main() {
    bool bubble[SIZE][SIZE];

    init(bubble);

    while (hasBubbles(bubble)) {
        print(bubble);

        int x1, y1, x2, y2;
        cout << "\nEnter region (x1 y1 x2 y2): ";
        cin >> x1 >> y1 >> x2 >> y2;

        popRegion(bubble, x1, y1, x2, y2);
    }

    cout << "\nAll bubbles popped!\n";
    return 0;
}