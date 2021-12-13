#include "logic.hpp"

int main()
{
    auto barista = CoffeeMaker();
    barista.order(-1);
    barista.order(1);
    auto my_coffee = barista.collect();

    std::cout << "I received " << my_coffee.size() << " cups of coffee." << std::endl;

    barista.order(5);
    barista.order(2);
    barista.order(3);
    auto my_other_coffee = barista.collect();

    std::cout << "I received " << my_other_coffee.size() << " cups of coffee." << std::endl;
}
