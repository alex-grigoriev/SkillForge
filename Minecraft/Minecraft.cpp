#include <iostream>
using namespace std;

int main() {
    const int SIZE = 5;
    const int HEIGHT = 10;

    int heights[SIZE][SIZE];
    int world[SIZE][SIZE][HEIGHT] = {0};

    // Ввод высот
    cout << "Enter 5x5 height matrix:\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cin >> heights[i][j];

            // Заполняем 3D массив
            for (int h = 0; h < heights[i][j]; h++) {
                world[i][j][h] = 1;
            }
        }
    }

    int level;
    cout << "Enter slice level (0-9): ";
    cin >> level;

    // Проверка уровня
    if (level < 0 || level >= HEIGHT) {
        cout << "Invalid level!\n";
        return 1;
    }

    // Вывод среза
    cout << "Slice at level " << level << ":\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (world[i][j][level])
                cout << "1 ";
            else
                cout << "0 ";
        }
        cout << endl;
    }

    return 0;
}