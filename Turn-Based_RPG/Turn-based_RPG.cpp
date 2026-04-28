#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

const int MAP_SIZE = 20;

struct Position
{
    int x, y;
};

struct Character
{
    string name;
    int hp;
    int armor;
    int damage;
    Position pos;
    bool isPlayer;
    bool alive = true;
};

// --- УРОН ---
void applyDamage(Character& target, int damage)
{
    int absorbed = min(target.armor, damage);
    target.armor -= absorbed;
    damage -= absorbed;
    target.hp -= damage;

    if (target.hp <= 0)
    {
        target.alive = false;
        cout << target.name << " died!\n";
    }
}

// --- ПРОВЕРКА ПОЗИЦИИ ---
bool isInside(int x, int y)
{
    return x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE;
}

Character* getCharacterAt(vector<Character>& chars, int x, int y)
{
    for (auto& c : chars)
    {
        if (c.alive && c.pos.x == x && c.pos.y == y)
            return &c;
    }
    return nullptr;
}

// --- ОТРИСОВКА ---
void drawMap(vector<Character>& chars)
{
    char grid[MAP_SIZE][MAP_SIZE];

    for (int i = 0; i < MAP_SIZE; i++)
        for (int j = 0; j < MAP_SIZE; j++)
            grid[i][j] = '.';

    for (auto& c : chars)
    {
        if (!c.alive) continue;
        grid[c.pos.y][c.pos.x] = c.isPlayer ? 'P' : 'E';
    }

    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
            cout << grid[i][j] << ' ';
        cout << endl;
    }
}

// --- СОХРАНЕНИЕ ---
void saveGame(const vector<Character>& chars)
{
    ofstream file("save.bin", ios::binary);
    if (!file)
    {
        cout << "Save error!\n";
        return;
    }

    int size = chars.size();
    file.write((char*)&size, sizeof(size));

    for (const auto& c : chars)
    {
        size_t len = c.name.size();
        file.write((char*)&len, sizeof(len));
        file.write(c.name.c_str(), len);

        file.write((char*)&c.hp, sizeof(c.hp));
        file.write((char*)&c.armor, sizeof(c.armor));
        file.write((char*)&c.damage, sizeof(c.damage));
        file.write((char*)&c.pos, sizeof(c.pos));
        file.write((char*)&c.isPlayer, sizeof(c.isPlayer));
        file.write((char*)&c.alive, sizeof(c.alive));
    }

    cout << "Game saved!\n";
}

// --- ЗАГРУЗКА ---
bool loadGame(vector<Character>& chars)
{
    ifstream file("save.bin", ios::binary);
    if (!file)
    {
        cout << "No save file!\n";
        return false;
    }

    chars.clear();

    int size;
    file.read((char*)&size, sizeof(size));

    for (int i = 0; i < size; i++)
    {
        Character c;

        size_t len;
        file.read((char*)&len, sizeof(len));

        c.name.resize(len);
        file.read(&c.name[0], len);

        file.read((char*)&c.hp, sizeof(c.hp));
        file.read((char*)&c.armor, sizeof(c.armor));
        file.read((char*)&c.damage, sizeof(c.damage));
        file.read((char*)&c.pos, sizeof(c.pos));
        file.read((char*)&c.isPlayer, sizeof(c.isPlayer));
        file.read((char*)&c.alive, sizeof(c.alive));

        chars.push_back(c);
    }

    cout << "Game loaded!\n";
    return true;
}

// --- СЛУЧАЙНОЕ ЧИСЛО ---
int randRange(int a, int b)
{
    return a + rand() % (b - a + 1);
}

// --- MAIN ---
int main()
{
    srand(time(0));

    vector<Character> characters;

    // --- СОЗДАНИЕ ИГРОКА ---
    Character player;
    cout << "Enter player name: ";
    cin >> player.name;

    cout << "HP Armor Damage: ";
    cin >> player.hp >> player.armor >> player.damage;

    player.pos = {randRange(0, 19), randRange(0, 19)};
    player.isPlayer = true;

    characters.push_back(player);

    // --- СОЗДАНИЕ ВРАГОВ ---
    for (int i = 0; i < 5; i++)
    {
        Character e;
        e.name = "Enemy #" + to_string(i + 1);
        e.hp = randRange(50, 150);
        e.armor = randRange(0, 50);
        e.damage = randRange(15, 30);
        e.pos = {randRange(0, 19), randRange(0, 19)};
        e.isPlayer = false;

        characters.push_back(e);
    }

    // --- ИГРОВОЙ ЦИКЛ ---
    while (true)
    {
        drawMap(characters);

        // поиск игрока
        Character* playerPtr = nullptr;
        for (auto& c : characters)
            if (c.isPlayer) playerPtr = &c;

        if (!playerPtr || !playerPtr->alive)
        {
            cout << "You lost!\n";
            break;
        }

        bool enemiesAlive = false;
        for (auto& c : characters)
            if (!c.isPlayer && c.alive)
                enemiesAlive = true;

        if (!enemiesAlive)
        {
            cout << "You win!\n";
            break;
        }

        string cmd;
        cout << "Command (L/R/U/D/save/load): ";
        cin >> cmd;

        if (cmd == "save")
        {
            saveGame(characters);
            continue;
        }

        if (cmd == "load")
        {
            loadGame(characters);
            continue;
        }

        int dx = 0, dy = 0;

        if (cmd == "L") dx = -1;
        if (cmd == "R") dx = 1;
        if (cmd == "U") dy = -1;
        if (cmd == "D") dy = 1;

        int nx = playerPtr->pos.x + dx;
        int ny = playerPtr->pos.y + dy;

        if (isInside(nx, ny))
        {
            Character* target = getCharacterAt(characters, nx, ny);

            if (target && !target->isPlayer)
            {
                applyDamage(*target, playerPtr->damage);
            }
            else if (!target)
            {
                playerPtr->pos = {nx, ny};
            }
        }

        // --- ХОД ВРАГОВ ---
        for (auto& c : characters)
        {
            if (c.isPlayer || !c.alive) continue;

            int dir = randRange(0, 3);
            int ex = c.pos.x;
            int ey = c.pos.y;

            if (dir == 0) ex--;
            if (dir == 1) ex++;
            if (dir == 2) ey--;
            if (dir == 3) ey++;

            if (!isInside(ex, ey)) continue;

            Character* target = getCharacterAt(characters, ex, ey);

            if (target)
            {
                if (target->isPlayer)
                {
                    applyDamage(*target, c.damage);
                }
                continue;
            }

            c.pos = {ex, ey};
        }
    }

    return 0;
}