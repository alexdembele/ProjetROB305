#include <iostream>
#include <cstring>
#include <vector>
#include "../inc/timespec.hpp"
#include "../inc/Mutex.hpp" 
struct Data 
{
    volatile double counter;
    unsigned long nLoops;
    bool protection;
    Mutex mutex; 
};

void incr(unsigned long nLoops, double* pCounter, Mutex& mutex, bool protection) {
    // Vérification du fonctionnement en mutex ou non
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

int main(int argc, char* argv[]) 
{
    bool protec; // Détermine le mode de fonctionnement
    if (argc != 4 && argc != 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <nombre_entier> <nombre de tâche> (<protected>)" << std::endl;
        return 1;
    }
    if (argc == 4) 
    {
        if (std::strcmp(argv[3], "protected") == 0) 
        {
            std::cout << "Fonctionnement avec Mutex" << std::endl;
            protec = true;
        } 
        else 
        {
            std::cout << "Fonctionnement sans Mutex" << std::endl;
            protec = false;
        }
    } 
    else 
    {
        std::cout << "Fonctionnement sans Mutex" << std::endl;
        protec = false;
    }

    unsigned long nLoops = (unsigned long)std::atoi(argv[1]);
    Data data = {0.0, nLoops, protec};
    timespec a = timespec_now();
    std::vector<pthread_t> incrementThread(std::atoi(argv[2]));
    for (auto& thid : incrementThread) 
    {
        pthread_create(&thid, nullptr, call_incr, &data);
    }

    for (auto& thid : incrementThread) 
    {
        pthread_join(thid, nullptr);
    }
    timespec b = timespec_now();
    timespec c =b-a;

    double temps_exec = timespec_to_ms(c)/1000;

    std::cout << "Valeur finale du counter : " << data.counter << std::endl;
    std::cout << "Temps d'exécution : " << temps_exec << " s" << std::endl;

    return 0;
}
