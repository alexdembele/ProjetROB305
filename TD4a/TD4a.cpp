#include <iostream>
#include <chrono>
#include "../inc/timespec.h"
#include "../inc/PosixThread.h"


class TestThread : public Thread 
{
protected:
    void run() override
    {
        
        for (int i = 0; i < 5; ++i) 
        {
            std::cout << "Thread is running..." << std::endl;
            timespec_wait(timespec_from_ms(2000));
        }
    }
};

int main() 
{
    TestThread testThread;
    int p_schedPolicy,p_priority;

    testThread.setScheduling(SCHED_RR,1);
    testThread.getSchedunling(&p_schedPolicy, &p_priority);
    std::cout << "Scheduling " << "schedPolicy : " << p_schedPolicy << " priority : " << p_priority<<std::endl;
    testThread.start();
    timespec_wait(timespec_from_ms(11000));    
    std::cout << "Execution time of the thread: " << testThread.execTime_ms() << " milliseconds" << std::endl;
    testThread.join();
    std::cout << "Tous les tests ont réussis!\n";

    return 0;
}