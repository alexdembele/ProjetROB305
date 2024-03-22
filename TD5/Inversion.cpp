#include <time.h>
#include <signal.h>
#include <thread>
#include <pthread.h>
#include <iostream>
#include "../inc/cpuLoop.h"
#include "../inc/Inversion.h"

// =========================================
// Classe Thread ABC
// =========================================
ThreadABC::ThreadABC(char * name,int beginTime_tick,int execTime_tick,int delayTime_tick,int mutexTime_tick,Mutex& mtx): beginTime_tick(beginTime_tick),execTime_tick(execTime_tick),delayTime_tick(delayTime_tick),mutexTime_tick(mutexTime_tick),mtx(mtx),name(name)
{ 
    counter =0;
    Calibrator myCalibration(200,10);
    std::this_thread::sleep_for(std::chrono::seconds(4));
    CpuLoop myLooper(myCalibration);
   
}

void ThreadABC::run()
{
    //pause avant de commencer le thread
    timespec_wait(timespec_from_ms(100*beginTime_tick));

    //execution avant de demander le mutex
    myLooper.runTime(100*mutexTime_tick);

    //Execution avec Mutex
    if (mutexTime_tick>0)
    {

        Mutex::Lock lock(mtx);
        myLooper.runTime(100*mutexTime_tick);
    }

    //fin execution, il n'y a pas de cas où on reprend le mutex dans le Gantt que l'on a fait, ce qui me permet de simplifier comme ça
    if (mutexTime_tick*2 < execTime_tick)
    {
        myLooper.runTime(100*(execTime_tick-2*mutexTime_tick));
    }
}

// =========================================
// Classe ThreadSurchargeCpu
// =========================================

ThreadSurchargeCpu::ThreadSurchargeCpu()
{
    counter=0;
}

void ThreadSurchargeCpu::run()
{
    for(int i=0; i<UINT_MAX;i++)
    {
        counter++;
    }
}