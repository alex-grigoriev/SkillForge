#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- ТИПЫ ---

enum RoomType
{
    LIVING,
    CHILDREN,
    BEDROOM,
    KITCHEN,
    BATHROOM
};

enum BuildingType
{
    HOUSE,
    GARAGE,
    SHED,
    BATHHOUSE
};

// --- СТРУКТУРЫ ---

struct Room
{
    RoomType type;
    double area;
};

struct Floor
{
    int ceiling_height;
    vector<Room> rooms;
};

struct Building
{
    BuildingType type;
    double area;
    bool has_stove = false; // для дома и бани

    vector<Floor> floors; // только для дома
};

struct Plot
{
    int number;
    double total_area;
    vector<Building> buildings;
};

struct Village
{
    vector<Plot> plots;
};

// --- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ---

RoomType inputRoomType()
{
    int t;
    cout << "Room type (0-living,1-children,2-bedroom,3-kitchen,4-bathroom): ";
    cin >> t;
    return static_cast<RoomType>(t);
}

BuildingType inputBuildingType()
{
    int t;
    cout << "Building type (0-house,1-garage,2-shed,3-bathhouse): ";
    cin >> t;
    return static_cast<BuildingType>(t);
}

// --- СОЗДАНИЕ ОБЪЕКТОВ ---

Room createRoom()
{
    Room r;
    r.type = inputRoomType();
    cout << "Room area: ";
    cin >> r.area;
    return r;
}

Floor createFloor()
{
    Floor f;
    cout << "Ceiling height: ";
    cin >> f.ceiling_height;

    int roomCount;
    cout << "Number of rooms (2-4): ";
    cin >> roomCount;

    for (int i = 0; i < roomCount; i++)
    {
        f.rooms.push_back(createRoom());
    }

    return f;
}

Building createBuilding()
{
    Building b;
    b.type = inputBuildingType();

    cout << "Building area: ";
    cin >> b.area;

    if (b.type == HOUSE || b.type == BATHHOUSE)
    {
        cout << "Has stove? (1-yes,0-no): ";
        cin >> b.has_stove;
    }

    if (b.type == HOUSE)
    {
        int floorsCount;
        cout << "Number of floors (1-3): ";
        cin >> floorsCount;

        for (int i = 0; i < floorsCount; i++)
        {
            b.floors.push_back(createFloor());
        }
    }

    return b;
}

Plot createPlot(int index)
{
    Plot p;
    p.number = index;

    cout << "Plot total area: ";
    cin >> p.total_area;

    int buildingCount;
    cout << "Number of buildings: ";
    cin >> buildingCount;

    for (int i = 0; i < buildingCount; i++)
    {
        p.buildings.push_back(createBuilding());
    }

    return p;
}

// --- РАСЧЁТ ---

double calculateBuildPercentage(const Village& v)
{
    double total_land = 0;
    double total_buildings = 0;

    for (const auto& plot : v.plots)
    {
        total_land += plot.total_area;

        for (const auto& b : plot.buildings)
        {
            total_buildings += b.area;
        }
    }

    if (total_land == 0) return 0;

    return (total_buildings / total_land) * 100.0;
}

// --- MAIN ---

int main()
{
    Village village;

    int plotCount;
    cout << "Number of plots: ";
    cin >> plotCount;

    for (int i = 0; i < plotCount; i++)
    {
        cout << "\n--- Plot " << i + 1 << " ---\n";
        village.plots.push_back(createPlot(i + 1));
    }

    double percent = calculateBuildPercentage(village);

    cout << "\nTotal building coverage: " << percent << "%\n";

    return 0;
}