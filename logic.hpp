#pragma once

#include <string>
#include <vector>
#include <iostream>

class Bean
{
public:
    bool ground;
    Bean() { ground = false; }
};

class Water {
public:
    int temperature;
    Water() { temperature = 30; }
};

class Hopper {
private:
    std::vector<Bean> beans;
    size_t capacity;
    friend class CoffeeTestHarness;
public:
    Hopper(int n = 200)
    {
        capacity = n;
        refill();
    }

    void refill() { while (beans.size() < capacity) { beans.emplace_back(); } }
    void print() { for (int i = 0; i < cur_level(); ++i) { if (i % 10 == 0) std::cout << "*"; } }
    int cur_level() { return beans.size(); }

    std::vector<Bean> take(int amount);
};

class Reservoir {
private:
    size_t capacity;
    std::vector<Water> water;
    friend class HeatSource;
    friend class CoffeeTestHarness;
public:
    Reservoir(int n = 1000)
    {
        capacity = n;
        refill();
    }

    void refill() { while (water.size() < capacity) { water.emplace_back(); } }
    void print() { for (int i = 0; i < cur_level(); ++i) { if (i % 10 == 0) std::cout << "*"; } }
    int cur_level() { return water.size(); }
    int check_temp() { return water.back().temperature; };

    std::vector<Water> drain(int amount);
};

class HeatSource {
private:
public:
    void heat(Reservoir &r);
};

class Grinder {
private:
public:
    void grind(std::vector<Bean> &beans);
};

class Cup {
private:
    friend class CoffeeTestHarness;
    std::vector<Bean> my_beans;
public:
    Cup()
    {
        std::cout << "I am a cup of air!\n";
    }

    Cup(std::vector<Water> water)
    {
        std::string size = (water.size() > 250) ? "big" : "small";
        std::cout << "I am a " << size << " cup of water!\n";
    }

    Cup(std::vector<Water> water, std::vector<Bean> beans)
    {
        std::string quality = (water.size() == 250 && beans.size() == 50) ? "great" : "mediocre";
        std::cout << "I am a " << quality << " cup of coffee!\n";
        my_beans = beans;
    }
};

class CoffeeMaker {
private:
    Hopper hopper;
    Reservoir reservoir;
    HeatSource heat_source;
    Grinder grinder;
    std::vector<Cup> cups;
    int cups_requested;
    friend class CoffeeTestHarness;
public:
    CoffeeMaker()
    {
        std::cout << "\n\tHello there! I make coffee.\n" << std::endl;

        // INITIALIZE OBJECTS
        hopper = Hopper();
        reservoir = Reservoir();
        heat_source = HeatSource();
        grinder = Grinder();
    }

    void order(int n);
    void brew();
    std::vector<Cup> collect();
};
