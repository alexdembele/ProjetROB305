#include <time.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include "../inc/timespec.h"


int main()
{
    // Test conversion ms/timespec
    std::cout << "Tests conversions ms/timespec ...\n";
    timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 500000000; // 1.5 seconds
    assert(fabs(timespec_to_ms(ts) - 1500.0) < 0.001);

    double ms = 2500.0;
    timespec result = timespec_from_ms(ms);
    assert(result.tv_sec == 2 && result.tv_nsec == 500000000);

    // Test timespec_negate
    std::cout << "Tests opposés ...\n";
    timespec positive_ts;
    positive_ts.tv_sec = 3;
    positive_ts.tv_nsec = 800000000; // 3.5 seconds
    timespec negative_ts = timespec_negate(positive_ts);
    assert(negative_ts.tv_sec == -4 && negative_ts.tv_nsec == 200000000);

    // Test timespec_add
    std::cout << "Tests addition/soustraction ...\n";
    timespec time1, time2;
    time1.tv_sec = 2;
    time1.tv_nsec = 500000000; // 2.5 seconds
    time2.tv_sec = 1;
    time2.tv_nsec = 500000000; // 1.5 seconds
    timespec sum = timespec_add(time1, time2);
    assert(sum.tv_sec == 4 && sum.tv_nsec == 0);

    //Test substract
    timespec temps1, temps2; 
    temps1.tv_sec = 2;
    temps1.tv_nsec = 500000000; // 2.5 seconds
    temps2.tv_sec = 3;
    temps2.tv_nsec = 800000000; // 3.8 seconds
    timespec sum2 = timespec_substract(temps1,temps2);
    assert(sum2.tv_sec == -2 && sum2.tv_nsec == 700000000);

    timespec diff = timespec_substract(time1, time2);
    assert(diff.tv_sec == 1 && diff.tv_nsec == 0);

    // test bool operator
    std::cout << "Tests opérateurs logiques ...\n";
    timespec t1, t2;
    t1.tv_sec = 3;
    t1.tv_nsec = 0;
    t2.tv_sec = 2;
    t2.tv_nsec = 0;

    assert((t1 - t2).tv_sec == 1 && (t1 - t2).tv_nsec == 0);
    assert((t1 + t2).tv_sec == 5 && (t1 + t2).tv_nsec == 0);
    assert((t1 == t2) == false);
    assert((t1 != t2) == true);
    assert((t1 > t2) == true);
    assert((t1 < t2) == false);

    // Test operator+= and operator-=
    std::cout << "Tests opérateurs +=, -= ...\n";
    timespec t3;
    t3.tv_sec = 1;
    t3.tv_nsec = 0;
    t3 += t1;
    assert(t3.tv_sec == 4 && t3.tv_nsec == 0);
    t3 -= t1;
    assert(t3.tv_sec == 1 && t3.tv_nsec == 0);

    std::cout << "Tous les tests ont réussis!\n";
    return 0 ;
}