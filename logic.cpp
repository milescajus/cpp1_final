#include "logic.hpp"

std::vector<Bean> Hopper::take(int amount)
{
    std::vector<Bean> beans_taken;

    if (amount <= cur_level()) {
        std::cout << "Taking beans from hopper... ";
        for (int i = 0; i < amount; ++i) {
            beans_taken.push_back(beans.back());
            beans.pop_back();
        } std::cout << "got beans!\n";
    } else {
        std::cout << "Insufficient beans for request! Please refill.\n";
    }

    return beans_taken;
}

std::vector<Water> Reservoir::drain(int amount)
{
    std::vector<Water> taken_water;

    if (amount <= cur_level()) {
        std::cout << "Draining water needed from reservoir... ";
        for (int i = 0; i < amount; ++i) {
            taken_water.push_back(water.back());
            water.pop_back();
        } std::cout << "water drained!\n";
    } else {
        std::cout << "Insufficient water for request! Please refill.\n";
    }

    return taken_water;
}

void HeatSource::heat(Reservoir &r)
{
    for (Water w : r.water) {
        w.temperature++;
    }
}

void Grinder::grind(std::vector<Bean> &beans)
{
    std::cout << "\tGrinding beans... ";
    for (size_t i = 0; i < beans.size(); ++i) {
        beans[i].ground = true;
    } std::cout << "beans ground!\n";
}

void CoffeeMaker::order(int n)
{
    if (n > 0 && n <= 4) {
        if (!cups.empty()) {
            std::cout << "\tWe still have " << cups.size() << " cups waiting for collection! Please collect() before ordering more.\n";
        } else {
            // BREW COFFEE
            cups_requested = n;
            cups.reserve(cups_requested);
            std::cout << "\t" << cups_requested << " cups of coffee coming up!\n";
            brew();
        }
    } else {
        // REJECT
        std::cout << "\tSorry, you can only order between 1 and 4 cups of coffee.\n" << std::endl;
    }
}

void CoffeeMaker::brew()
{
    if (reservoir.check_temp() < 100) {
        std::cout << "\tHeating the water reservoir... ";
        while (reservoir.check_temp() < 100) {
            heat_source.heat(reservoir);
        } std::cout << "steamy!\n";
    }

    while ((int) cups.size() < cups_requested) {
        std::cout << "\t";
        auto water = reservoir.drain(250);

        if (water.size() < 250) {
            reservoir.refill();
            std::cout << "\t";
            water = reservoir.drain(250);
        }

        std::cout << "\t";
        auto beans = hopper.take(50);

        if (beans.size() < 50) {
            hopper.refill();
            std::cout << "\t";
            beans = hopper.take(50);
        }

        grinder.grind(beans);

        std::cout << "\tPouring a damn fine cup of coffee... ";
        cups.emplace_back(water, beans);
    }
}

std::vector<Cup> CoffeeMaker::collect()
{
    if (!cups.empty()) {
        std::cout << "\tHere is your coffee :)\n";
    } else {
        std::cout << "\tHere is your empty vector because something went wrong :)\n";
    }

    std::cout << std::endl;

    auto tmp = cups;
    std::vector<Cup>().swap(cups);  // clear and reallocate (shrink)

    return tmp;
}
