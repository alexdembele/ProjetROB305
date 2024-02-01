#include <cstring>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
<<<<<<< HEAD
#include <pthread.h>
=======
>>>>>>> ac18d14d3c73c9c28209ab8155d79efb7532586d
#include "../inc/timespec.hpp"
struct Data 
{
    
    volatile double  counter;
    unsigned long nLoops;
    bool protection;
    pthread_mutex_t mutex;
};


void incr(unsigned long nLoops, double* pCounter,pthread_mutex_t* mutex, bool protection)
{
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
    bool protec;
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
    unsigned int nTasks = (unsigned int)std::atoi(argv[2]);

    Data data = {  0.0 , nLoops, protec};
    pthread_mutex_init(&data.mutex, nullptr);
    pthread_t incrementThread[nTasks];
    for(int i=0;i<nTasks;i++)
    {
        pthread_create(&incrementThread[i], nullptr, call_incr, &data);
    }
    
    /*timespec a = timespec_now();
    incr(nLoops, &counter);
    timespec b = timespec_now();

    timespec c =b-a;

    double temps_exec = timespec_to_ms(c);*/
    
    
    for (int i=0; i<3; ++i) 
    {
        pthread_join(incrementThread[i], nullptr);
    }
    pthread_mutex_destroy(&data.mutex);
    std::cout << "Valeur finale du counter : " << data.counter << std::endl;
    //std::cout << "temps d'exécution : " << temps_exec<< " ms" << std::endl;

    return 0 ;
}