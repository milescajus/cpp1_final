#include "logic.hpp"

std::vector<Water> Reservoir::drain(int amount)
{
    std::vector<Water> taken_water;

    if (amount <= Reservoir::cur_level) {
        std::cout << "Draining water needed from reservoir...\n";
        Reservoir::cur_level -= amount;
        for (int i = 0; i < amount; ++i) {
            taken_water.push_back(Water());
        }
    }

    return taken_water;
}

std::vector<Bean> Grinder::grind(int amount, Hopper h)
{
    std::vector<Bean> ground_beans;

    if (amount <= h.cur_level) {
        std::cout << "Taking beans from hopper...\n";
        h.cur_level -= amount;
        std::cout << "Grinding beans!\n";
        for (int i = 0; i < amount; ++i) {
            ground_beans.push_back(Bean());
        }
    }

    return ground_beans;
}

void CoffeeMaker::brew()
{
    CoffeeMaker::heat_source.heat(CoffeeMaker::reservoir);

    for (int i = 0; i < CoffeeMaker::order; i++) {
        std::vector<Water> water = reservoir.drain(250);
        std::vector<Bean> beans = grinder.grind(50, CoffeeMaker::hopper);
        std::cout << "Pouring a damn fine cup of coffee...\n";
        auto cup = Cup(water, beans);
        CoffeeMaker::cups.push_back(cup);
    }
}
