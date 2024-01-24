#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED

#include <time.h>
#include <signal.h>


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
        struct sigaction sa;
        struct sigevent sev;
        struct itimerspec its;


};
#endif