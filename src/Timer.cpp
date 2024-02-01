#include <time.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <cstring>
#include <iostream>
#include "../inc/Timer.hpp"
#include "../inc/timespec.hpp"

Timer::Timer()
{
    struct sigaction sa;
    struct sigevent sev;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = call_callback;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr =  (void*) this;

    timer_create(CLOCK_REALTIME, &sev, &tid);
}

Timer::~Timer()
{
    stop();
    timer_delete(tid);
}

void Timer::start(double duration_ms)
{
    struct itimerspec its;
    its.it_value=timespec_from_ms(duration_ms);
    its.it_interval=timespec_from_ms(0);

    timer_settime(tid, 0, &its, nullptr);
}

void Timer::stop()
{
    // Désarmement de la minuterie
    struct itimerspec its;
    its.it_value=timespec_from_ms(0);
    its.it_interval=timespec_from_ms(0);

    
}

void Timer::call_callback(int /*sig*/, siginfo_t * si, void*)
{
    Timer* pTimer = (Timer*)si->si_value.sival_ptr;
    pTimer->callback();
}

void PeriodicTimer::startPeriodic(double interval_ms)
{
    struct itimerspec its;
    its.it_value=timespec_from_ms(interval_ms);
    its.it_interval=timespec_from_ms(interval_ms);
    std::cout << "startPeriodic"  << std::endl;
    timer_settime(tid, 0, &its, nullptr);
}

CountDown::CountDown(int initialValue)
{
    Count = initialValue;
}

void CountDown::startCountDown()
{
    // Appelle la fonction startPeriodic avec la valeur initiale
    startPeriodic(1000);
}

void CountDown::callback() 
{
    if(Count >0)
    {
        std::cout << "Compteur : " << Count << std::endl;
        Count--;
                
    }
    else
    {
        stop();
    }
}


int main()
{
    int nSecond = 10;
    CountDown countdown(nSecond);
    
    // Démarrage du compte à rebours
    countdown.startCountDown();
    
        
    std::this_thread::sleep_for(std::chrono::seconds(nSecond+1));
        
    
    
    
    return 0;
}

