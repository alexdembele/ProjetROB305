#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED

#include <time.h>
#include <signal.h>
#include <iostream>
#include "../inc/timespec.hpp"


class Timer
{
    protected:
        timer_t tid;
        virtual void callback() = 0;//abstract

    public:
        Timer();
        virtual ~Timer();
        void start(double duration_ms);
        void stop();

    private:
        static void call_callback(int sig, siginfo_t * si, void*);
};

class PeriodicTimer:  public  Timer
{
    public:        
        void startPeriodic(double interval_ms) ;    
};

class CountDown : public PeriodicTimer 
{
    private:
        int Count;
    public:
        CountDown(int initialValue) ;
        // Fonction pour démarrer le compte à rebours
        void startCountDown(); 
        virtual void callback () override;
};


#endif