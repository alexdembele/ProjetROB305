#include <iostream>
#include <pthread.h>
#include <climits>
#include "../inc/timespec.h"
#include "../inc/Mutex.h"

// =========================================
// Classe Mutex
// =========================================

Mutex::Mutex()
{
    pthread_mutex_init(&posixMutexId, NULL);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&posixMutexId);
}

void Mutex::lock() 
{
    pthread_mutex_lock(&posixMutexId);
}

bool Mutex::lock(double timeout_ms) 
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts+= timespec_from_ms(timeout_ms);

    int result = pthread_mutex_timedlock(&posixMutexId, &ts);
    if (result == ETIMEDOUT) 
    {
        return false;
    }
    return true;
}

void Mutex::unlock() 
{
    pthread_mutex_unlock(&posixMutexId);
}

// =========================================
// Classe Monitor
// =========================================

Mutex::Monitor::Monitor(Mutex& mtx) : mutex(mtx)
{
    pthread_cond_init(&mutex.posixCondId, nullptr);
}

void Mutex::Monitor::wait()
{
    pthread_cond_wait(&mutex.posixCondId, &mutex.posixMutexId);
}

bool Mutex::Monitor::wait(double timeout_ms)
{
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts+= timespec_from_ms(timeout_ms);

    int result = pthread_cond_timedwait(&mutex.posixCondId, &mutex.posixMutexId, &ts);
    if (result == ETIMEDOUT) 
    {
        return false;
    }
    return true;
}

void Mutex::Monitor::notify()
{
    pthread_cond_signal(&mutex.posixCondId);
}

void Mutex::Monitor::notifyAll()
{
    pthread_cond_broadcast(&mutex.posixCondId);
}


// =========================================
// Classe Lock
// =========================================
Mutex::Lock::Lock(Mutex& mtx) :  Monitor(mtx)
{
    mutex.lock();
}

Mutex::Lock::Lock(Mutex& mtx, double timeout_ms) : Monitor(mtx)
{
    if (!mutex.lock(timeout_ms)) 
    {
        throw TimeoutException();
    }
}

Mutex::Lock::~Lock()
{
    mutex.unlock();
}



// =========================================
// Classe Semaphore
// =========================================

void Semaphore::take() 
{
    Mutex::Lock lock(*this); 
    while (counter == 0)
    { 
        lock.wait();
    }
    --counter; 
}

void Semaphore::give() 
{
    Mutex::Lock lock(*this); 
    if (counter < maxCount)
    {
        ++counter;
    }
}

bool Semaphore::take(double timeout_ms) 
{
    Mutex::Lock lock(*this); 
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts += timespec_from_ms(timeout_ms);

    while (counter == 0) 
    {
        if (!lock.wait(timeout_ms))
        { 
            return false;
        }
    }
    --counter; 
    return true;
}

unsigned int Semaphore::getCounter()
{
    return counter;
}



