#include <iostream>
#include <chrono>
#include "../inc/timespec.hpp"
#include "../inc/PosixThread.hpp"


class TestThread : public Thread 
{
protected:
    virtual void* run(void* v_thread) 
    {
        
        for (int i = 0; i < 5; ++i) 
        {
            std::cout << "Thread is running..." << std::endl;
            Thread::sleep_ms(1000); 
        }
        return nullptr;
    }
};

int main() {
   
    TestThread testThread;
    
    testThread.start();
    std::cout << "Yousk2"<<std::endl;
    
    Thread::sleep_ms(7000); 
    std::cout << "Yousk2"<<std::endl;
    
    std::cout << "Execution time of the thread: " << testThread.execTime_ms() << " milliseconds" << std::endl;

    testThread.join();

    return 0;
}