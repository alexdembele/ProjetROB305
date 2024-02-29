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
    std::this_thread::sleep_for(std::chrono::seconds(nSecond+1));
    return 0;
}