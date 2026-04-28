#include <iostream>
#include <string>
using namespace std;

// ===== Класс Toy =====
class Toy {
private:
    string name;

public:
    Toy(const string& name) : name(name) {}

    ~Toy() {
        cout << "Toy " << name << " was dropped" << endl;
    }

    string getName() const {
        return name;
    }
};

// ===== shared_ptr_toy =====
class shared_ptr_toy {
private:
    Toy* ptr;
    int* count;

    void release() {
        if (count) {
            (*count)--;

            if (*count == 0) {
                delete ptr;
                delete count;
            }
        }

        ptr = nullptr;
        count = nullptr;
    }

public:
    // Конструктор по умолчанию
    shared_ptr_toy() : ptr(nullptr), count(nullptr) {}

    // Конструктор с именем
    shared_ptr_toy(const string& name) {
        ptr = new Toy(name);
        count = new int(1);
    }

    // Копирующий конструктор
    shared_ptr_toy(const shared_ptr_toy& other) {
        ptr = other.ptr;
        count = other.count;

        if (count) {
            (*count)++;
        }
    }

    // Оператор присваивания
    shared_ptr_toy& operator=(const shared_ptr_toy& other) {
        if (this == &other) return *this;

        // Освобождаем текущий ресурс
        release();

        // Копируем
        ptr = other.ptr;
        count = other.count;

        if (count) {
            (*count)++;
        }

        return *this;
    }

    // Деструктор
    ~shared_ptr_toy() {
        release();
    }

    // reset
    void reset() {
        release();
    }

    // get
    Toy* get() const {
        return ptr;
    }

    // use_count
    int use_count() const {
        return count ? *count : 0;
    }

    // имя игрушки
    string getToyName() const {
        if (ptr)
            return ptr->getName();
        return "Nothing";
    }
};

// ===== make_shared_toy =====
shared_ptr_toy make_shared_toy(const string& name) {
    return shared_ptr_toy(name);
}

// ===== Тест =====
int main() {
    shared_ptr_toy toy_01 = make_shared_toy("ball");
    shared_ptr_toy toy_02(toy_01);
    shared_ptr_toy toy_03("duck");

    cout << "=================================================" << endl;
    cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
         << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
         << toy_03.getToyName() << " links:" << toy_03.use_count() << endl;

    cout << "=================================================" << endl;

    toy_02 = toy_03;

    cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
         << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
         << toy_03.getToyName() << " links:" << toy_03.use_count() << endl;

    cout << "=================================================" << endl;

    toy_01.reset();

    cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
         << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
         << toy_03.getToyName() << " links:" << toy_03.use_count() << endl;

    cout << "=================================================" << endl;

    return 0;
}