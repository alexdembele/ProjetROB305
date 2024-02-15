#include <time.h>
#include <signal.h>
#include <thread>
#include <pthread.h>
#include "../inc/timespec.hpp"
#include "../inc/PosixThread.hpp"


// =========================================
// Posixthread
// =========================================
PosixThread::PosixThread(): posixId(0),isActive(false)
{
    pthread_attr_init(&posixAttr);
}

PosixThread::PosixThread(pthread_t posixId): posixId(posixId),isActive(true)
{
    pthread_attr_init(&posixAttr);
    int policy;
    sched_param schedp;
    if (pthread_getschedparam(posixId, &policy, &schedp) < 0)
    {
        isActive = false;
        posixId = 0;
    }
    pthread_attr_setschedpolicy(&posixAttr,policy);
    pthread_attr_setschedparam(&posixAttr, &schedp);



}

PosixThread::~PosixThread()
{

}

void PosixThread::start(void* (*threadFunc) (void*) , void* threadArg)
{
    isActive=true;
    pthread_create(&posixId, &posixAttr, threadFunc, &threadArg);
}

void PosixThread::join()
{
    if (isActive) 
    {
        pthread_join(posixId, NULL);
        isActive = false;
    }
}

bool PosixThread::join(double timeout_ms)
{
    if (isActive) 
    {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts+= timespec_from_ms(timeout_ms);

        int ret = pthread_timedjoin_np(posixId, NULL, &ts);
        if (ret == ETIMEDOUT) 
        {
            return false;
        }
        isActive = false;
    }
    return true;
}

bool PosixThread::setScheduling(int schedPolicy, int priority)
{
    struct sched_param param;
    param.sched_priority = priority;

    if (pthread_setschedparam(posixId, schedPolicy, &param) != 0) 
    {
        return false;
    }
    return true;

}

bool PosixThread::getSchedunling(int* p_schedPolicy, int* p_priority)
{
    struct sched_param param;
    int policy;

    if (pthread_getschedparam(posixId, &policy, &param) != 0)
    {
        return false;
    }
    *p_schedPolicy = policy;
    *p_priority = param.sched_priority;
    return true;   
}

// =========================================
// Classe Thread
// =========================================
Thread::Thread()
{

}

Thread::~Thread()
{
    
}

void Thread::start()
{
    PosixThread::start(&Thread::call_run(), this);
}

void* Thread::run(void* v_thread) 
{
    return NULL;
}

void* Thread::call_run(void* thread) 
{
    Thread* myTHread = (Thread*)thread;
    return myThread->run(thread);
}

double Thread::startTime_ms()
{
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    return timespec_to_ms(abstime);
}

double Thread::stopTime_ms()
{
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    return timespec_to_ms(abstime);
}




int main()
{
    return 0;
}

