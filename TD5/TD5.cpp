#include <iostream>
#include <thread>
#include <chrono>
#include "../inc/timespec.hpp"
#include "../inc/cpuLoop.hpp"
#include "../inc/Mutex.hpp" 

struct Data 
{
    volatile double counter;
    unsigned long nLoops;
    bool protection;
    Mutex mutex; 
};

// Fonction exécutée par chaque thread
void cpuIntensiveTask() 
{
    int i =0;
    while (true) 
    {
        i++;
    }
}

void A()
{

}

void B()
{

}

void C()
{

}

//tick en 100 ms
int main() 
{
    // Nombre de threads à exécuter
    const int numThreads = 4;

    //Calibration
    Calibrator myCalibrator(200,10);
    CpuLoop myLoop(myCalibrator);

    

    // Création et démarrage des threads
    std::thread threads[numThreads];
    for (int i = 0; i < numThreads; ++i) 
    {
        threads[i] = std::thread(cpuIntensiveTask);
    }

    // Attente pendant un certain temps
    std::this_thread::sleep_for(std::chrono::seconds(10)); // Temps d'exécution des threads

    // Arrêt des threads
    for (int i = 0; i < numThreads; ++i) 
    {
        threads[i].join();
    }

    return 0;
}
