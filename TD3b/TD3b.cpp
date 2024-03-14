#include <time.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <cstring>
#include <iostream>
#include "../inc/Timer.hpp"
#include "../inc/timespec.hpp"

int main(int argc, char* argv[])
{
    int nSecond = 10;

    if(argc >1) 
    {
        nSecond = (int) std::atoi(argv[1]);
    }
    CountDown countdown(nSecond);
    
    // Démarrage du compte à rebours
    countdown.startCountDown();
    //On laisse le temps à l'autre thread de s'exécuter
    std::this_thread::sleep_for(std::chrono::seconds(nSecond+3));
    return 0;
}