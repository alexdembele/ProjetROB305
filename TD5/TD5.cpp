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
// classe derive de thread pour savoir si il y a section critique et savoir si l'on se trouve avant apres ou pendant, instancier 3 tâches

// Fonction exécutée par chaque thread
void cpuIntensiveTask() 
{
    int i =0;
    while (true) 
    {
        i++;
    }
}

void inc(unsigned long duration_ms ,double* pCounter, Mutex& mutex, bool protected)
{
    if (protection) 
    {
        for (unsigned int u = 0; u < nLoops; u++) 
        {
            Mutex::Lock lock(mutex);
            *pCounter += 1;
        }
    }
    else 
    {
        for (unsigned int u = 0; u < nLoops; u++) 
        {
            *pCounter += 1;
        }
    }

}

void* call_incr(void* v_data) 
{
    Data* p_data = (Data*)v_data;
    incr(p_data->nLoops, (double*)&p_data->counter, p_data->mutex, p_data->protection);
    return v_data;
}

//tick en 100 ms
int main() 
{
    // Nombre de threads à exécuter
    const int numThreads = 4;

    //Calibration
    Calibrator myCalibrator(200,10);
    CpuLoop myLoop(myCalibrator);
    Data dataA = {0.0, nLoops, protec};
    Data dataB = {0.0, nLoops, protec};
    Data dataC = {0.0, nLoops, protec};

    

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
