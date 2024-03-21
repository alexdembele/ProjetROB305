#include <time.h>
#include <iostream>
#include "../inc/timespec.h"
#include "../inc/Chrono.h"

Chrono::Chrono()
{
    restart(); 
}

void Chrono::stop()
{
    m_stopTime = timespec_now();
    active = false;
}

void Chrono::restart()
{
    m_startTime = timespec_now();
    active = true;
}

bool Chrono::isActive()
{
    return active;
}

double Chrono::lap()
{
    if(isActive())
    {
        return timespec_to_ms(timespec_now()-m_startTime);
    }
    else
    {
        return timespec_to_ms(m_stopTime-m_startTime);
    }
}