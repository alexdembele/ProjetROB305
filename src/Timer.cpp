#include <time.h>
#include <signal.h>
#include "../inc/Timer.hpp"
#include "../inc/timespec.hpp"

Timer::Timer()
{
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

    its.it_value=timespec_from_ms(duration_ms);
    its.it_interval=timespec_from_ms(0);

    timer_settime(tid, 0, &its, nullptr);
}

void Timer::stop()
{
    // Désarmement de la minuterie
    its.it_value=timespec_from_ms(0);
    its.it_interval=timespec_from_ms(0);

    
}

void Timer::call_callback(int /*sig*/, siginfo_t * si, void*)
{
    
}

