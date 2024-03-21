#include <iostream>
#include <chrono>
#include <pthread.h>
#include <thread>
#include "../inc/Inversion.h"
// tick = 100ms calibrer ce temps avec calibrator


int main()
{
    Mutex mtx;
    //Creation des threads
    ThreadABC A("Thread A",30,40,60,10,mtx);
    ThreadABC B("Thread B",30,10,70,0,mtx);
    ThreadABC C("Thread C",0,50,110,20,mtx);

    //Assignation des priorité
    A.setScheduling(SCHED_RR,32);
    B.setScheduling(SCHED_RR,33);
    C.setScheduling(SCHED_RR,34);

    //Execution
    A.start();
    B.start();
    C.start();


    return 0;
}

