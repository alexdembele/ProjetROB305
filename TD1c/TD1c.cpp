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
};

void incr(unsigned long nLoops, double* pCounter)
{
    for(unsigned int u=0; u< nLoops; u++)
    {
        *pCounter+=1;
    }
}

void* call_incr(void* v_data)
{
    Data* p_data = (Data*) v_data;
    incr(p_data->nLoops, (double *)&p_data->counter);
    return v_data;
}

int main(int argc, char* argv[])
{
    if (argc != 2 ) 
    {
        std::cerr << "Usage: " << argv[0] << " <nombre_entier>  " << std::endl;
        return 1;
    }
    
    unsigned long nLoops = (unsigned long)std::atoi(argv[1]);
    Data data = {  0.0 , nLoops};
    timespec a = timespec_now();
    std::vector<pthread_t> incrementThread(1);
    for(auto& thid :incrementThread )
    {
        pthread_create(&thid, nullptr, call_incr, &data);
    }
    
    for(auto& thid :incrementThread )
    {
        pthread_join(thid, nullptr);
    }
    timespec b = timespec_now();
    timespec c =b-a;

    double temps_exec = timespec_to_ms(c)/1000; //on divise par 1000 pour convertir en s

    std::cout << "Valeur finale du counter : " << data.counter << std::endl;
    std::cout << "temps d'exécution : " << temps_exec<< " s" << std::endl;

    return 0 ;
}