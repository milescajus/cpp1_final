#pragma once

#define MAX_BEANS 200
#define MAX_WATER 1000

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Bean {};
class Water {};

class Hopper {
private:
    Bean beans[MAX_BEANS];
    int current;
public:
    Hopper()
    {
        for (int i = 0; i < MAX_BEANS; ++i) {
            beans[i] = Bean();
        }

        current = MAX_BEANS;
    }
};

class Reservoir {
private:
    Water water[MAX_WATER];
    int current;
    int temperature;
public:
    Reservoir()
    {
        for (int i = 0; i < MAX_WATER; ++i) {
            water[i] = Water();
        }

        current = MAX_WATER;
        temperature = 30;
    }

    Water* drain(int amount);
};

class HeatSource {
private:
public:
    void heat(Reservoir &r);
};

class Grinder {
private:
public:
    Bean* grind(int amount, Hopper h);
};

class Cup {
private:
public:
};

class CoffeeMaker {
private:
    Hopper h;
    Reservoir r;
    HeatSource hs;
    Grinder g;
public:
    CoffeeMaker(int n)
    {
        if (n > 0 && n <= 4) {
            // INITIALIZE OBJECTS
            h = Hopper();
            r = Reservoir();
            hs = HeatSource();
            g = Grinder();
        } else {
            // REJECT
            std::cout << "INVALID NUMBER OF CUPS -- VALID: (0, 4]" << std::endl;
        }
    }

    Cup brew();
};
