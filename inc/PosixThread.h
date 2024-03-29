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
        virtual ~Thread();
        void start();
    
    protected:
        virtual void run() = 0;
    
    protected:
        static void* call_run(void* thread);

    private:
        timespec startTime;
        timespec stopTime;
    
    public:
        static void sleep_ms(double delay_ms);
        double startTime_ms();
        double stopTime_ms();
        double execTime_ms();
};

#endif