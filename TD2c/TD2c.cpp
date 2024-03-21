#include <cstring>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <pthread.h>
#include <vector>
#include <sched.h> // For scheduling policies
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
    // Verification of mutex functionality
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
    bool protec = true; // Determine the operation mode
    if (argc != 4) 
    {
        std::cerr << "Usage: " << argv[0] << " <nombre_entier> <nombre de tâche> <scheduling_policy>" << std::endl;
        return 1;
    }

    if(std::strcmp(argv[3], "SCHED_RR") == 0)
    {
        std::cout << "Scheduling policy: SCHED_RR" << std::endl;
        struct sched_param schedParam;
        schedParam.sched_priority = sched_get_priority_max(SCHED_RR);
        pthread_setschedparam(pthread_self(), SCHED_RR, &schedParam);
    }
    else if(std::strcmp(argv[3], "SCHED_FIFO") == 0)
    {
        std::cout << "Scheduling policy: SCHED_FIFO" << std::endl;
        struct sched_param schedParam;
        schedParam.sched_priority = sched_get_priority_max(SCHED_FIFO);
        pthread_setschedparam(pthread_self(), SCHED_FIFO, &schedParam) ;
    }
    else
    {
        std::cout << "Scheduling policy: SCHED_OTHER (default)" << std::endl;
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

    double temps_exec = timespec_to_ms(c)/1000; // Dividing by 1000 to convert to seconds

    std::cout << "Final value of the counter: " << data.counter << std::endl;
    std::cout << "Execution time: " << temps_exec << " s" << std::endl;

    return 0;
}
