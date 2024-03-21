#ifndef Fifo_h_INCLUDED
#define Fifo_h_INCLUDED

#include <pthread.h>
#include <stdexcept>
#include <queue>
#include <climits>
#include "../inc/timespec.h"
#include "../inc/Mutex.hpp"

class EmptyException : public std::out_of_range
{
    public:
        EmptyException() : std::out_of_range("Fifo is empty") {}
};


template<typename T>
class Fifo: public Mutex
{
    private:
        std::queue<T> elements;
    public:
        void push(T element);
        T pop();
        T pop(double timeout_ms);
};

template<typename T>
void Fifo<T>::push(T element)
{
    Mutex::Lock lock(*this);
    elements.push(element);
}

template<typename T>
T Fifo<T>::pop()
{
    Mutex::Lock lock(*this);
    if (elements.empty())
    {
        throw EmptyException();
    }
    T element = elements.front();
    elements.pop();
    return element;
}

template<typename T>
T Fifo<T>::pop(double timeout_ms)
{
    Mutex::Lock lock(*this);
    
    timespec ts = timespec_now();
    ts += timespec_from_ms(timeout_ms);

    while (elements.empty())
    {
        if (!lock.wait(timeout_ms))
        {
            throw EmptyException();
        }
    }

    T element = elements.front();
    elements.pop();
    return element;
}

#endif