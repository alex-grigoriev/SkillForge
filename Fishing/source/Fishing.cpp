#include "Fishing.h"

template <typename T>
constexpr T SLEEP(T seconds)
{
    return sleep(seconds);
}

struct Fish {};

struct Boot {};

struct Field
{
    Fish *fish;
    Boot *boot;
};

void load(Field field[])
{
    srand(time (nullptr));
    int count = 0, rnd = 0;
    while(count < 3)
    {
        rnd = rand() % 9;
        if(field[rnd].boot != (Boot*) 103)
        {
            field[rnd].boot = (Boot*) 103;
            ++count;
        }
    }

    count = 0;
    while(count < 1)
    {
        rnd = rand() % 9;
        if(field[rnd].boot != (Boot*) 103)
        {
            field[rnd].fish = (Fish*) 101;
            ++count;
        }
    }
}

void ponds(Field field[])
{
    int input = 0;
    cin >> input;

    if(cin.fail() || input < 1 || input > 9)
    {
        cin.clear();
        cin.ignore(256, '\n');
        throw invalid_argument("ERROR");
    }

    --input;
    srand(time (nullptr));
    int rnd = rand() % 9 + 1;
    SLEEP(rnd);

    if(field[input].fish == (Fish*) 101)
    {
        throw invalid_argument("FISH");
    }
    else if(field[input].boot == (Boot*) 103)
    {
        throw invalid_argument("BOOT");
    }
}