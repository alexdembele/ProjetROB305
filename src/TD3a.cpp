#include <time.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "../inc/timespec.hpp"
#include "../inc/Chrono.hpp"

int main()
{
    Chrono myChrono;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    myChrono.stop();
    std::cout << "Chrono : "  << myChrono.lap()<< "ms"<<std::endl;

    return 0;
}