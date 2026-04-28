#pragma once

#include <iostream>
#include <ctime>
#include <unistd.h>

using namespace std;

template <typename T>
constexpr T SLEEP(T seconds);

struct Fish;

struct Boot;

struct Field;

void load(Field *field);

void ponds(Field *field);