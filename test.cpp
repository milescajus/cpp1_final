#include "utils.h"
#include "logic.hpp"

class CoffeeTestHarness : public AbstractTestHarness {
private:
    int order_coffee(int n)
    {
        CoffeeMaker barista = CoffeeMaker();
        std::cout << "I would like " << n << " coffees.\n\n";
        barista.order(n);
        auto coffee = barista.collect();
        std::cout << "I received " << coffee.size() << " coffees.\n\n";
        return coffee.size();
    }

    int order_after_no_collect()
    {
        CoffeeMaker barista = CoffeeMaker();
        barista.order(3);
        std::cout << "I would like " << 1 << " coffees.\n\n";
        barista.order(1);
        auto coffee = barista.collect();
        std::cout << "I received " << coffee.size() << " coffees.\n\n";
        return coffee.size();
    }

    int collect_before_order()
    {
        CoffeeMaker barista = CoffeeMaker();
        auto coffee = barista.collect();
        std::cout << "I received " << coffee.size() << " coffees.\n\n";
        return coffee.size();
    }

    int refill_water()
    {
        CoffeeMaker barista = CoffeeMaker();
        barista.reservoir.water = std::vector<Water>(100);
        barista.order(1);
        return barista.collect().size();
    }

    int refill_beans()
    {
        CoffeeMaker barista = CoffeeMaker();
        barista.hopper.beans = std::vector<Bean>(10);
        barista.order(1);
        return barista.collect().size();
    }

    int water_level_check()
    {
        CoffeeMaker barista = CoffeeMaker();
        barista.order(4);
        return barista.reservoir.cur_level();
    }

    int bean_level_check()
    {
        CoffeeMaker barista = CoffeeMaker();
        barista.order(4);
        return barista.hopper.cur_level();
    }

    int bean_grinding_check()
    {
        CoffeeMaker barista = CoffeeMaker();
        barista.order(1);
        bool ground = true;
        auto my_beans = barista.collect().back().my_beans;

        // if any bean is not ground, ground will be set to false
        for (auto bean : my_beans) { ground = bean.ground; }

        return ground;
    }

public:
    CoffeeTestHarness()
    {
        register_test_func("1: Ordering negative coffees.",
                [this]() -> void { assert_equal(0, order_coffee(-1)); });
        register_test_func("2: Ordering too many coffees.",
                [this]() -> void { assert_equal(0, order_coffee(5)); });
        register_test_func("3: Ordering zero coffees.",
                [this]() -> void { assert_equal(0, order_coffee(0)); });
        register_test_func("4: Ordering a valid amount of coffee!",
                [this]() -> void { assert_equal(4, order_coffee(4)); });
        register_test_func("5: Ordering without collecting first.",
                [this]() -> void { assert_equal(3, order_after_no_collect()); });
        register_test_func("6: Collecting without ordering first.",
                [this]() -> void { assert_equal(0, collect_before_order()); });
        register_test_func("7: Insufficient water.",
                [this]() -> void { assert_equal(1, refill_water()); });
        register_test_func("8: Insufficient beans.",
                [this]() -> void { assert_equal(1, refill_beans()); });
        register_test_func("9: Water gets consumed.",
                [this]() -> void { assert_equal(0, water_level_check()); });
        register_test_func("A: Beans get consumed.",
                [this]() -> void { assert_equal(0, bean_level_check()); });
        register_test_func("B: Beans get ground.",
                [this]() -> void { assert_equal(1, bean_grinding_check()); });
    }
};

class GlobalTestManager : public TestManager {
    public:
        GlobalTestManager() { add_test("CoffeeMaker Tests", CoffeeTestHarness()); }
};

int main()
{
    srand(time(NULL));

    auto tr = GlobalTestManager();
    tr.execute();
}
