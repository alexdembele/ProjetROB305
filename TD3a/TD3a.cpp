#include <time.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "../inc/timespec.hpp"
#include "../inc/Chrono.hpp"

int main(int argc, char* argv[])
{
    int duree_ms=1000;
    if (argc >2) 
    {
        std::cerr << "Usage: " << argv[0] << " <temps en ms> " << std::endl;
        return 1;
    }
    if(argc ==2)
    {
        duree_ms = std::atoi(argv[1]);
    }
    std::cout << "Départ Chrono"  <<std::endl;
    Chrono myChrono;
    std::this_thread::sleep_for(std::chrono::milliseconds(duree_ms));
    myChrono.stop();
    std::cout << "Fin Chrono"  <<std::endl;
    //on rajoute un délai pour bien voir que le chrono s'est arrêté
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Chrono : "  << myChrono.lap()<< "ms"<<std::endl;

    return 0;
}