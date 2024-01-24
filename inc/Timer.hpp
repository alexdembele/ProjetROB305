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

        
        void startPeriodic(double interval_ms) 
        {
            struct itimerspec its;
            its.it_value=timespec_from_ms(interval_ms);
            its.it_interval=timespec_from_ms(interval_ms);

            timer_settime(tid, 0, &its, nullptr);
        };
       
        
};

class CountDown : public PeriodicTimer {
    private:
        int Count;
public:
    
    
    CountDown(int initialValue) 
    {
        Count = initialValue;
    };

    

    // Fonction pour démarrer le compte à rebours
    void startCountDown() {
        // Appelle la fonction startPeriodic avec la valeur initiale
        startPeriodic(1000);
    }

    void callback()
    {
        if(Count >0)
        {
            std::cout << "Compteur" << Count << std::endl;
            Count--;

            
        }
        else
        {
            stop();
        }
    }
    
};


#endif