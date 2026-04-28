#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex station_mutex;

// --- ФУНКЦИЯ ПОЕЗДА ---
void train(char name, int travel_time)
{
    cout << "Train " << name << " departed and is on the way (" 
         << travel_time << " sec)\n";

    // движение до вокзала
    this_thread::sleep_for(chrono::seconds(travel_time));

    cout << "Train " << name << " arrived at station\n";

    // ожидание свободного вокзала
    station_mutex.lock();

    cout << "Train " << name << " is at the station\n";
    cout << "Enter 'depart' to send train " << name << ": ";

    string cmd;
    while (true)
    {
        cin >> cmd;
        if (cmd == "depart")
            break;
        cout << "Type 'depart' to continue: ";
    }

    cout << "Train " << name << " departed from station\n";

    station_mutex.unlock();
}

// --- MAIN ---
int main()
{
    int tA, tB, tC;

    cout << "Enter travel time for trains A, B, C (seconds): ";
    cin >> tA >> tB >> tC;

    thread trainA(train, 'A', tA);
    thread trainB(train, 'B', tB);
    thread trainC(train, 'C', tC);

    trainA.join();
    trainB.join();
    trainC.join();

    cout << "All trains have passed the station.\n";

    return 0;
}