#ifndef THREAD_H
#define THREAD_H

#include <time.h>
#include <signal.h>
#include <thread>
#include <pthread.h>

class PosixThread
{
    private:
        pthread_t posixId;
        pthread_attr_t posixAttr;

    protected:
        bool isActive;

    public:
        PosixThread();
        PosixThread(pthread_t posixId);
        ~PosixThread();
        void start(void* (*threadFunc) (void*) , void* threadArg);
        void join();
        bool join(double timeout_ms);
        bool setScheduling(int schedPolicy, int priority);
        bool getSchedunling(int* p_schedPolicy, int* p_priority);
};


class Thread : public PosixThread
{
    public:
        Thread();
        ~Thread();
        void start();
    
    protected:
        void* run(void* v_thread);
    
    private:
        static void* call_run(void* thread);
    
    public:
        static void sleep_ms(double delay_ms);
        double startTime_ms();
        double stopTime_ms();
        double execTime_ms();

};


#endif