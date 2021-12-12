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
public:
    int cur_level;

    Hopper()
    {
        for (int i = 0; i < MAX_BEANS; ++i) {
            beans[i] = Bean();
        }

        cur_level = MAX_BEANS;
    }
};

class Reservoir {
private:
    Water water[MAX_WATER];
public:
    int cur_level;
    int temperature;

    Reservoir()
    {
        for (int i = 0; i < MAX_WATER; ++i) {
            water[i] = Water();
        }

        cur_level = MAX_WATER;
        temperature = 30;
    }

    std::vector<Water> drain(int amount);
};

class HeatSource {
private:
public:
    void heat(Reservoir &r) { r.temperature++; };
};

class Grinder {
private:
public:
    std::vector<Bean> grind(int amount, Hopper h);
};

class Cup {
private:
public:
    Cup()
    {
        std::cout << "I am a cup of air!";
    }

    Cup(std::vector<Water> water)
    {
        std::cout << "I am a cup of water!";
    }

    Cup(std::vector<Water> water, std::vector<Bean> beans)
    {
        std::string quality = (water.size() == 250 && beans.size() == 50) ? "great" : "mediocre";
        std::cout << "I am a " << quality << " cup of coffee!";
    }
};

class CoffeeMaker {
private:
    Hopper hopper;
    Reservoir reservoir;
    HeatSource heat_source;
    Grinder grinder;
    int order;
public:
    std::vector<Cup> cups;

    CoffeeMaker(int n)
    {
        if (n > 0 && n <= 4) {
            // INITIALIZE OBJECTS
            order = n;
            hopper = Hopper();
            reservoir = Reservoir();
            heat_source = HeatSource();
            grinder = Grinder();
        } else {
            // REJECT
            std::cout << "INVALID NUMBER OF CUPS -- VALID: (0, 4]" << std::endl;
        }
    }

    void brew();
};
