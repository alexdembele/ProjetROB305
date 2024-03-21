#include <cstring>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <pthread.h>
#include <vector>
#include "../inc/timespec.h"

struct Data 
{
    volatile double  counter;
    unsigned long nLoops;
    bool protection;
    pthread_mutex_t mutex;
};

void incr(unsigned long nLoops, double* pCounter,pthread_mutex_t* mutex, bool protection)
{
    //verification du fonctionnement en mutex ou non
    if(protection)
    {
        for(unsigned int u=0; u< nLoops; u++)
        {
            pthread_mutex_lock(mutex);
            *pCounter+=1;
            pthread_mutex_unlock(mutex);
        }
    }
    else
    {
        for(unsigned int u=0; u< nLoops; u++)
        {
            *pCounter+=1;
        }
    }
}

void* call_incr(void* v_data)
{
    Data* p_data = (Data*) v_data;
    incr(p_data->nLoops, (double *)&p_data->counter,&p_data->mutex,p_data->protection);
    return v_data;
}

int main(int argc, char* argv[])
{
    bool protec; //determine le mode de fonctionnement
    if (argc != 4 && argc !=3) 
    {
        std::cerr << "Usage: " << argv[0] << " <nombre_entier> <nombre de tâche> (<protected>)" << std::endl;
        return 1;
    }
    if(argc== 4)
    {
        if(std::strcmp(argv[3], "protected") == 0)
        {
            std::cout << "Fonctionnement avec Mutex" << std::endl;
            protec=true;
        }
        else
        {
            std::cout << "Fonctionnement sans Mutex" << std::endl;
            protec=false;
        }
    }
    else
    {
        std::cout << "Fonctionnement sans Mutex" << std::endl;
        protec=false;
    }
    
    unsigned long nLoops = (unsigned long)std::atoi(argv[1]);
    Data data = {  0.0 , nLoops, protec};
    pthread_mutex_init(&data.mutex, nullptr);
    timespec a = timespec_now();
    std::vector<pthread_t> incrementThread(std::atoi(argv[2]));
    for(auto& thid :incrementThread )
    {
        pthread_create(&thid, nullptr, call_incr, &data);
    }
    
    for(auto& thid :incrementThread )
    {
        pthread_join(thid, nullptr);
    }
    pthread_mutex_destroy(&data.mutex);
    timespec b = timespec_now();
    timespec c =b-a;

    double temps_exec = timespec_to_ms(c)/1000; //on divise par 1000 pour cenvertir en s

    std::cout << "Valeur finale du counter : " << data.counter << std::endl;
    std::cout << "temps d'exécution : " << temps_exec<< " s" << std::endl;

    return 0 ;
}