#ifndef Inversion_h_INCLUDED
#define Inversion_h_INCLUDED
#include <time.h>
#include <signal.h>
#include <thread>
#include <pthread.h>
#include <iostream>
#include "../inc/timespec.h"
#include "../inc/PosixThread.h"
#include "../inc/Mutex.hpp"
#include "../inc/cpuLoop.h"


class ThreadABC : public Thread
{
    private:
        char* name;
        int beginTime_tick;
        int execTime_tick;
        int delayTime_tick;
        int mutexTime_tick;
        int counter;
        CpuLoop myLooper;
        Mutex& mtx;
    protected:
        void run() override;
    public:
        ThreadABC(char* name,int beginTime_tick,int execTime_tick,int delayTime_tick,int mutexTime_tick,Mutex& mtx);
};

class ThreadSurchargeCpu : public Thread
{
    private:
        int counter;
    protected:
        void run() override;
    public:
        ThreadSurchargeCpu();
};

#endif