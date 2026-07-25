#include "DamageTracker.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Original Tracker ===\n";

    DamageTracker dt;

    dt.addHit(DamageType::PHYSICAL, 20, 1.0, false); // 20
    dt.addHit(DamageType::FIRE, 15, 2.5, true);      // 30
    dt.addHit(DamageType::ICE, 40, 4.0, false);      // 40
    dt.addHit(DamageType::FIRE, 10, 5.5, true);      // 20
    dt.addHit(DamageType::PHYSICAL, 50, 8.0, false); // 50
    dt.addHit(DamageType::POISON, 25, 9.2, true);    // 50

    dt.printAllHits();

    dt.printTotalDamage();
    dt.printAvgDamage();
    dt.printHighestDamage();
    dt.printComboDamage(10.0, 3.0);


    std::cout << "\n=== Damage Type Test ===\n";

    dt.printDamageByType(DamageType::FIRE);
    dt.printDamageByType(DamageType::PHYSICAL);


    std::cout << "\n=== Copy Constructor Test ===\n";

    DamageTracker dt2 = dt;

    dt2.addHit(DamageType::ICE, 100, 10.0, false);

    std::cout << "Original:\n";
    dt.printTotalDamage();

    std::cout << "Copy:\n";
    dt2.printTotalDamage();


    std::cout << "\n=== Assignment Operator Test ===\n";

    DamageTracker dt3;

    dt3.addHit(DamageType::POISON, 999, 20.0, false);

    dt3 = dt;

    dt3.printTotalDamage();


    std::cout << "\n=== Empty Tracker Test ===\n";

    DamageTracker empty;

    empty.printTotalDamage();
    empty.printAvgDamage();
    empty.printHighestDamage();
    empty.printComboDamage(5.0, 2.0);


    return 0;
}