#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// --- ДАННЫЕ ---
vector<string> dishes = {"Pizza", "Soup", "Steak", "Salad", "Sushi"};

queue<string> orders;        // заказы от официанта
queue<string> readyOrders;   // готовые блюда

mutex orderMutex;
mutex readyMutex;
mutex runningMutex;          // [FIX] мьютекс для running
mutex deliveredMutex;        // [FIX] мьютекс для deliveredCount

bool running = true;
int deliveredCount = 0;

// --- СЛУЧАЙНОЕ ЧИСЛО ---
int randRange(int a, int b)
{
    return a + rand() % (b - a + 1);
}

// --- ПОСТУПЛЕНИЕ ЗАКАЗОВ ---
void waiter()
{
    while (true)
    {
        {
            lock_guard<mutex> lock(runningMutex);
            if (!running) break;  // [FIX] проверка running с защитой
        }
        
        this_thread::sleep_for(chrono::seconds(randRange(5, 10)));

        string dish = dishes[randRange(0, dishes.size() - 1)];

        {
            lock_guard<mutex> lock(orderMutex);
            orders.push(dish);
            cout << "[Order] New order: " << dish << endl;
        }
    }
}

// --- ГОТОВКА ---
void cook()
{
    while (true)
    {
        {
            lock_guard<mutex> lock(runningMutex);
            if (!running) break;  // [FIX] проверка running с защитой
        }
        
        string dish;

        {
            lock_guard<mutex> lock(orderMutex);
            if (orders.empty())
            {
                this_thread::sleep_for(chrono::milliseconds(100));  // [FIX] небольшая задержка вместо continue
                continue;
            }

            dish = orders.front();
            orders.pop();
        }

        cout << "[Kitchen] Cooking: " << dish << endl;

        this_thread::sleep_for(chrono::seconds(randRange(5, 15)));

        {
            lock_guard<mutex> lock(readyMutex);
            readyOrders.push(dish);
            cout << "[Kitchen] Ready: " << dish << endl;
        }
    }
}

// --- ДОСТАВКА ---
void courier()
{
    while (true)
    {
        // Check if the simulation should continue
        {
            lock_guard<mutex> lock(runningMutex);
            if (!running) break;
        }

        string dish;
        {
            lock_guard<mutex> lock(readyMutex);
            if (readyOrders.empty())
            {
                this_thread::sleep_for(chrono::milliseconds(100));
                continue;
            }
            dish = readyOrders.front();
            readyOrders.pop();
        }

        cout << "[Courier] Delivering: " << dish << endl;
        // Simulate delivery time
        this_thread::sleep_for(chrono::seconds(randRange(2, 5)));

        {
            lock_guard<mutex> lock(deliveredMutex);
            ++deliveredCount;
        }
        cout << "[Courier] Delivered: " << dish << " (total delivered: " << deliveredCount << ")" << endl;
    }
    // End of courier function
}

// --- MAIN ---
int main()
{
    srand(time(0));

    thread t1(waiter);
    thread t2(cook);
    thread t3(courier);

    t1.join();
    t2.join();
    t3.join();

    cout << "All orders delivered. Closing restaurant.\n";

    return 0;
}