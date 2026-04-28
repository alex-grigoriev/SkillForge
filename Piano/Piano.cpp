#include <iostream>
#include <string>
using namespace std;

enum note
{
    DO = 1,
    RE = 2,
    MI = 4,
    FA = 8,
    SOL = 16,
    LA = 32,
    SI = 64
};

int main() {
    string input;
    cout << "Enter chord (1-7): ";
    cin >> input;

    int notes = 0;

    // Формируем битовую маску
    for (char c : input) {
        if (c >= '1' && c <= '7') {
            int digit = c - '1'; // 0..6
            notes |= (1 << digit);
        }
    }

    cout << "Chord contains:\n";

    if (notes & DO)  cout << "DO ";
    if (notes & RE)  cout << "RE ";
    if (notes & MI)  cout << "MI ";
    if (notes & FA)  cout << "FA ";
    if (notes & SOL) cout << "SOL ";
    if (notes & LA)  cout << "LA ";
    if (notes & SI)  cout << "SI ";

    cout << endl;

    return 0;
}
