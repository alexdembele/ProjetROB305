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
    pthread_create(&posixId, &posixAttr, threadFunc, threadArg);
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
    if(!isActive)
    {
        startTime = timespec_now();
        PosixThread::start(&call_run, this); 
    }
}

void* Thread::call_run(void* thread) 
{
    Thread* theThread = (Thread*)thread;
    theThread->run();
    theThread->stopTime = timespec_now();
    return nullptr;
}

double Thread::startTime_ms()
{
    return timespec_to_ms(startTime);
}

double Thread::stopTime_ms()
{
    return timespec_to_ms(stopTime);
}

double Thread::execTime_ms()
{
    return stopTime_ms()-startTime_ms();
}

void Thread::sleep_ms(double delay_ms) 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(delay_ms)));
}






