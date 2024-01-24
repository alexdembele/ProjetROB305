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
    sev.sigev_value.sival_ptr =  (void*) &tid;

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

int main()
{
    std::cout << "Yousk1" << std::endl;
    CountDown countdown(5);
    std::cout << "Yousk2" << std::endl;
    // Démarrage du compte à rebours
    countdown.startCountDown();
    std::cout << "Yousk3" << std::endl;
    
    std::cout << "Yousk4" << std::endl;
    
    
    return 0;
}

