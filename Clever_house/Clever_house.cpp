#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

using namespace std;

// -------------------- Данные --------------------
enum Switch : int {
    LIGHTS_INSIDE = 1,
    LIGHTS_OUTSIDE = 2,
    HEATERS = 4,
    WATER_PIPE_HEATING = 8,
    CONDITIONER = 16
};

struct State {
    int switches_state = 0;
    int color_temp = 5000;
};

// -------------------- Функции --------------------

// Преобразуем строку ввода в нужные значения
tuple<int,int,bool,bool> parse_input(const string& line) {
    stringstream ss(line);
    int temp_inside, temp_outside;
    string movement_str, lights_str;
    ss >> temp_inside >> temp_outside >> movement_str >> lights_str;
    bool movement = (movement_str == "yes");
    bool lights_input = (lights_str == "on");
    return {temp_inside, temp_outside, movement, lights_input};
}

// Водопровод
void water_pipe(State& st, int temp_outside) {
    if (temp_outside < 0) {
        st.switches_state |= WATER_PIPE_HEATING;
    } else if (temp_outside > 5) {
        st.switches_state &= ~WATER_PIPE_HEATING;
    }
}

// Уличный свет
void garden_lights(State& st, int hour, bool movement) {
    bool is_evening = (hour >= 16 || hour < 5);
    if (is_evening && movement) {
        st.switches_state |= LIGHTS_OUTSIDE;
    } else {
        st.switches_state &= ~LIGHTS_OUTSIDE;
    }
}

// Отопление
void heaters(State& st, int temp_inside) {
    if (temp_inside < 22) st.switches_state |= HEATERS;
    else if (temp_inside >= 25) st.switches_state &= ~HEATERS;
}

// Кондиционер
void conditioner(State& st, int temp_inside) {
    if (temp_inside >= 30) st.switches_state |= CONDITIONER;
    else if (temp_inside <= 25) st.switches_state &= ~CONDITIONER;
}

// Свет внутри (ручное)
void lights_inside(State& st, bool on) {
    if (on) st.switches_state |= LIGHTS_INSIDE;
    else st.switches_state &= ~LIGHTS_INSIDE;
}

// Цветовая температура
void update_color_temp(State& st, int hour) {
    if (hour == 0) {
        st.color_temp = 5000;
    } else if (hour >= 16 && hour <= 20) {
        int step = (5000 - 2700) / 4;
        st.color_temp = 5000 - step * (hour - 16);
    }
}

// Вывод
void output(const State& st) {
    if (st.switches_state & LIGHTS_INSIDE) {
        cout << "Color temperature: " << st.color_temp << "K" << endl;
    }
}

// -------------------- MAIN --------------------
int main() {
    State st;
    for (int hour = 0; hour < 48; ++hour) {
        int current_hour = hour % 24;
        cout << "Temperature inside, temperature outside, movement, lights:" << endl;
        string line; getline(cin, line);
        auto [temp_in, temp_out, movement, lights_on] = parse_input(line);
        water_pipe(st, temp_out);
        garden_lights(st, current_hour, movement);
        heaters(st, temp_in);
        conditioner(st, temp_in);
        lights_inside(st, lights_on);
        update_color_temp(st, current_hour);
        output(st);
    }
    return 0;
}
