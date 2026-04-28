#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// перемешивание
void init(vector<char>& table) {
    vector<char> letters = {'A','B','C','D','E'};

    vector<char> pairs;
    for (char c : letters) {
        pairs.push_back(c);
        pairs.push_back(c);
    }

    random_shuffle(pairs.begin(), pairs.end());

    table = pairs;
}

// вывод
void print(const vector<char>& visible) {
    for (int i = 0; i < visible.size(); i++) {
        cout << i+1 << ":" << visible[i] << "  ";
        if ((i+1) % 5 == 0) cout << endl;
    }
    cout << endl;
}

// проверка завершения
bool isWin(const vector<char>& visible) {
    for (char c : visible)
        if (c == '*') return false;
    return true;
}

int main() {
    srand(time(0));

    int size = 10;
    vector<char> table;
    vector<char> visible(size, '*'); // скрытые

    init(table);

    cout << "=== MEMORY GAME ===\n";

    while (!isWin(visible)) {
        print(visible);

        int a, b;
        cout << "Enter two positions: ";
        cin >> a >> b;

        if (a < 1 || a > size || b < 1 || b > size || a == b) {
            cout << "Invalid input!\n";
            continue;
        }

        // показать
        visible[a-1] = table[a-1];
        visible[b-1] = table[b-1];

        print(visible);

        if (table[a-1] == table[b-1]) {
            cout << "Match!\n";
        } else {
            cout << "No match!\n";

            // скрыть обратно
            visible[a-1] = '*';
            visible[b-1] = '*';
        }
    }

    cout << "YOU WIN!\n";
    return 0;
}