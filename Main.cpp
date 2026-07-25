#include <iostream>
#include "DamageTracker.hpp"

int main()
{
    DamageTracker dt;

    dt.addHit(20, 1.0, false);  // 20
    dt.addHit(15, 2.5, true);   // 30
    dt.addHit(40, 4.0, false);  // 40
    dt.addHit(10, 5.5, true);   // 20
    dt.addHit(50, 8.0, false);  // 50
    dt.addHit(25, 9.2, true);   // 50

    DamageTracker dt2;
    dt2 = dt;

    dt2.printTotalDamage();
    dt2.printAvgDamage();
    dt2.printHighestDamage();
    dt2.printComboDamage(10.0, 3.0);

    return 0;
}