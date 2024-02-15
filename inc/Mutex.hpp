#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

#include <pthread.h>
#include <stdexcept>
#include <queue>

class Mutex
{
    public:
        class Monitor;
        class Lock;

    public:
        Mutex();
        ~Mutex();

    
    private:
        pthread_mutex_t posixMutexId;
        pthread_cond_t posixCondId;
        void lock();
        bool lock(double timeout_ms);
        void unlock();

};

class TimeoutException : public std::runtime_error
{
public:
    TimeoutException() : std::runtime_error("Timeout occurred while waiting for lock") {}
};

class EmptyException : public std::out_of_range
{
public:
    EmptyException() : std::out_of_range("Fifo is empty") {}
};



class Mutex::Monitor
{
    public:
        Monitor(Mutex& mtx);
        void wait();
        bool wait(double timeout_ms);
        void notify();
        void notifyAll();

    protected:
        Mutex& mutex;

};

class Mutex::Lock : public Mutex::Monitor
{
    public:
        Lock(Mutex& mtx);
        Lock(Mutex& mtx, double timeout_ms);
        ~Lock();


};

class Semaphore: public Mutex
{
    private:
        unsigned int counter;
        unsigned int maxCount;
    
    public:
        Semaphore(unsigned int initCount = 0, unsigned int countMax = 10);
        void give();
        void take();
        bool take(double timeout_ms);
};

template <typename T>
class Fifo: public Mutex
{
    private:
        std::queue<T> elements;
    
    public:
        void push(T element) 
        {
        // mutex
        // elements.push(element);
        }
        T pop()
        {

        }

        T pop(double timeout_ms)
        {

        }
};
#endif