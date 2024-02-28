#ifndef Chrono_h_INCLUDED
#define Chrono_h_INCLUDED

#include <time.h>
#include <iostream>
#include "../inc/timespec.hpp"

class Chrono
{
    private:
        timespec m_startTime;
        timespec m_stopTime;
        bool active;
    public:
        Chrono();
        void stop();
        void restart();
        bool isActive();
        double lap();


};

#endif