#include <cstring>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <pthread.h>
#include <vector>
#include <climits>
#include "../inc/timespec.h"

struct Data 
{
    volatile double  counter;
    unsigned long nLoops;  
    bool pStop;  
    double duration_ms;
};
// =========================================
// Fonctions du compteur
// =========================================


void incr(unsigned long nLoops, double* pCounter,bool* pStop)
{
    for (unsigned long u = 0; u < nLoops; u++)
    {
        if (*pStop)
        {  
           break; 
        } 
        *pCounter += 1;
    }
}

void* call_incr(void* v_data)
{
    Data* p_data = (Data*) v_data;
    incr(p_data->nLoops, (double *)&p_data->counter,&p_data->pStop);
    return v_data;
}

// =========================================
// Fonctions du timer
// =========================================


void timer(bool* pStop,double* duration_ms)
{
    timespec_wait(timespec_from_ms(*duration_ms));
   *pStop =true;
}

void* call_timer(void* v_data)
{
    Data* p_data = (Data*) v_data;
    timer(&p_data->pStop, &p_data->duration_ms);
    return v_data;
}


// =========================================
// Fonction pour calibration
// =========================================
void calib(double* a, double* b)
{
    unsigned long nLoops = (unsigned long)UINT_MAX;
    bool pStop = false;
    pthread_t incrementThread;
    pthread_t timerThread;
    //premiere mesure
    std::cout << "Premiere mesure : 4s"<<std::endl;
    Data data = {  0.0 , nLoops,pStop,4000};
    timespec debut = timespec_now();
   
    pthread_create(&incrementThread, nullptr, call_incr, &data);
    pthread_create(&timerThread, nullptr, call_timer, &data);

    pthread_join(incrementThread, nullptr);
    pthread_join(timerThread, nullptr);

    timespec fin = timespec_now();
    timespec duree =fin-debut;
    double temps_exec1 = timespec_to_ms(duree);
    int finalValue1 = data.counter;

    //deuxieme mesure
    std::cout << "Deuxieme mesure : 6s"<<std::endl;
    data = {  0.0 , nLoops,pStop,6000};
    debut = timespec_now();
   
    pthread_create(&incrementThread, nullptr, call_incr, &data);
    pthread_create(&timerThread, nullptr, call_timer, &data);

    pthread_join(incrementThread, nullptr);
    pthread_join(timerThread, nullptr);

    fin = timespec_now();
    duree =fin-debut;
    double temps_exec2 = timespec_to_ms(duree);
    int finalValue2 = data.counter;

    *a = (finalValue2-finalValue1)/(temps_exec2-temps_exec1);
    *b = finalValue1-(*a * temps_exec1);
}





int main()
{
       
    double a,b;
    calib(&a,&b);

    std::cout << "Valeur des coefficients de la droite l(t) = a*t +b : a  =" << a << " ; b = "<< b<<std::endl;
    std::cout << "Test des valeurs  pour une durée de 5s : "<<std::endl;
    unsigned int nLoops = (unsigned int ) a * 5000 + b;
    std::cout << "nLoops =  "<<nLoops <<std::endl;
    Data data = {  0.0 , nLoops,false,10000};
    pthread_t incrementThread;
    timespec debut = timespec_now();
   
    pthread_create(&incrementThread, nullptr, call_incr, &data);
    pthread_join(incrementThread, nullptr);
    timespec fin = timespec_now();
    timespec duree =fin-debut;
    double temps_exec = timespec_to_ms(duree);
    std::cout << "Temps d'execution : "<< temps_exec <<"ms" <<std::endl;
    std::cout << "Valeur du compteur : "<< data.counter <<"ms" <<std::endl;



    return 0 ;
}