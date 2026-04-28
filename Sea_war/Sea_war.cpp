#include <iostream>
using namespace std;

const int SIZE = 10;

// Поля игроков
bool field1[SIZE][SIZE] = {false};
bool field2[SIZE][SIZE] = {false};

// Поля выстрелов (что игрок видит)
char fog1[SIZE][SIZE];
char fog2[SIZE][SIZE];

bool isValid(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

void initFog(char fog[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            fog[i][j] = '.';
}

void printField(char field[SIZE][SIZE]) {
    cout << "  ";
    for (int j = 0; j < SIZE; j++) cout << j << " ";
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

bool canPlace(bool field[SIZE][SIZE], int x1, int y1, int x2, int y2) {
    if (!isValid(x1,y1) || !isValid(x2,y2)) return false;
    if (x1 != x2 && y1 != y2) return false;

    int dx = (x2 > x1) ? 1 : (x2 < x1 ? -1 : 0);
    int dy = (y2 > y1) ? 1 : (y2 < y1 ? -1 : 0);

    int x = x1, y = y1;

    while (true) {
        if (field[x][y]) return false;
        if (x == x2 && y == y2) break;
        x += dx;
        y += dy;
    }

    return true;
}

void placeShip(bool field[SIZE][SIZE], int size) {
    while (true) {
        int x1, y1, x2, y2;

        if (size == 1) {
            cout << "Enter 1 cell (x y): ";
            cin >> x1 >> y1;
            x2 = x1; y2 = y1;
        } else {
            cout << "Enter start and end (x1 y1 x2 y2): ";
            cin >> x1 >> y1 >> x2 >> y2;
        }

        int length = max(abs(x2 - x1), abs(y2 - y1)) + 1;

        if (length != size) {
            cout << "Wrong ship size!\n";
            continue;
        }

        if (!canPlace(field, x1, y1, x2, y2)) {
            cout << "Invalid placement!\n";
            continue;
        }

        int dx = (x2 > x1) ? 1 : (x2 < x1 ? -1 : 0);
        int dy = (y2 > y1) ? 1 : (y2 < y1 ? -1 : 0);

        int x = x1, y = y1;

        while (true) {
            field[x][y] = true;
            if (x == x2 && y == y2) break;
            x += dx;
            y += dy;
        }

        break;
    }
}

void placeAllShips(bool field[SIZE][SIZE]) {
    int ships[] = {1,1,1,1, 2,2,2, 3,3, 4};

    for (int s : ships) {
        cout << "Place ship of size " << s << endl;
        placeShip(field, s);
    }
}

bool shoot(bool field[SIZE][SIZE], char fog[SIZE][SIZE], int x, int y) {
    if (fog[x][y] != '.') {
        cout << "Already shot here!\n";
        return false;
    }

    if (field[x][y]) {
        cout << "Hit!\n";
        field[x][y] = false;
        fog[x][y] = 'X';
        return true;
    } else {
        cout << "Miss!\n";
        fog[x][y] = '*';
        return false;
    }
}

bool hasShips(bool field[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (field[i][j]) return true;
    return false;
}

void gameLoop() {
    int player = 1;

    while (true) {
        cout << "\nPlayer " << player << " turn\n";

        if (player == 1)
            printField(fog2);
        else
            printField(fog1);

        int x, y;
        cout << "Enter shot (x y): ";
        cin >> x >> y;

        if (!isValid(x,y)) {
            cout << "Invalid coords!\n";
            continue;
        }

        bool hit;

        if (player == 1)
            hit = shoot(field2, fog2, x, y);
        else
            hit = shoot(field1, fog1, x, y);

        if (player == 1 && !hasShips(field2)) {
            cout << "Player 1 wins!\n";
            break;
        }

        if (player == 2 && !hasShips(field1)) {
            cout << "Player 2 wins!\n";
            break;
        }

        if (!hit)
            player = (player == 1 ? 2 : 1);
    }
}

int main() {
    initFog(fog1);
    initFog(fog2);

    cout << "=== Player 1 placing ships ===\n";
    placeAllShips(field1);

    cout << "\n=== Player 2 placing ships ===\n";
    placeAllShips(field2);

    cout << "\n=== Game Start ===\n";
    gameLoop();

    return 0;
}