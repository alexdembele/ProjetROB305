#include <time.h>
#include <iostream>
#include "../inc/timespec.hpp"


double timespec_to_ms(const timespec& time_ts)
{
    double ms = 0;
    ms += time_ts.tv_sec * 1000;
    ms+= time_ts.tv_nsec / 1000000;
    return ms ;
}

timespec timespec_from_ms(double time_ms)
{
    timespec t;
    t.tv_sec = time_ms / 1000;
    t.tv_nsec =  (time_ms -(t.tv_sec*1000) )* 1000000;
    return t;
}

timespec timespec_now()
{
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    return abstime;
}

timespec timespec_negate(const timespec& time_ts) {

    timespec result;
    int sec = -time_ts.tv_sec;
    int nsec = -time_ts.tv_nsec;
    // Gestion des nanosecondes qui doivent être positives
    if (nsec < 0) 
    {
        sec -= 1;
        nsec += 1e9;
    }
    result.tv_sec= sec;
    result.tv_nsec= nsec;

    return result;
}


timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts) 
{
    int sec = time1_ts.tv_sec + time2_ts.tv_sec;
    int nsec = time1_ts.tv_nsec + time2_ts.tv_nsec; 

    //gestion des nanosecondes qui peuvent depasser la seconde
    if (nsec >= 1e9) 
    {
        sec += 1;
        nsec -= 1e9;
    }
    timespec result;
    result.tv_sec= sec;
    result.tv_nsec= nsec;

    return result;
}

timespec timespec_substract(const timespec& time1_ts, const timespec& time2_ts)
{
    return timespec_add(time1_ts, timespec_negate(time2_ts));
}

timespec operator- (const timespec& time_ts) 
{
    return timespec_negate(time_ts);
}

timespec operator+ (const timespec& time1_ts, const timespec& time2_ts) {
    return timespec_add(time1_ts, time2_ts);

}

timespec operator- (const timespec& time1_ts, const timespec& time2_ts) 
{
    return timespec_substract(time1_ts, time2_ts);
}

timespec& operator+= (timespec& time_ts, const timespec& delay_ts) 
{
    time_ts = timespec_add(time_ts, delay_ts);
    return time_ts;
}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts) 
{
    time_ts = timespec_substract(time_ts, delay_ts);
    return time_ts;
}

bool operator== (const timespec& time1_ts, const timespec& time2_ts) 
{
    return (time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec);
}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts) 
{
    return !(time1_ts == time2_ts);
}

bool operator< (const timespec& time1_ts, const timespec& time2_ts) 
{
    if (time1_ts.tv_sec < time2_ts.tv_sec) 
    {
        return true;
    } 
    else if (time1_ts.tv_sec == time2_ts.tv_sec) 
    {
        return time1_ts.tv_nsec < time2_ts.tv_nsec;
    } 
    else
    {
        return false;
    }
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts) 
{
    return !(time1_ts < time2_ts || time1_ts == time2_ts);
}



