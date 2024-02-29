#include <time.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <cstring>
#include <iostream>
#include <pthread.h>


struct Data 
{
    volatile bool stop;
    volatile double counter;
};

void* incrementer(void* v_data) 
{
    Data* p_data = (Data*) v_data;
    while (not p_data->stop) 
    {
        p_data->counter += 1.0;
    }
    return v_data;
}

int main(int argc, char* argv[])
{
    Data data = { false, 0.0 };
    pthread_t incrementThread;
    
    pthread_create(&incrementThread, nullptr, incrementer, &data);
    for (char cmd = 'r'; cmd != 's'; std::cin >> cmd)
    {
        std::cout << "Type 's' to stop: " << std::flush;
    }
    data.stop = true;
    pthread_join(incrementThread, nullptr);
    std::cout << "Counter value = " << data.counter << std::endl;
    
    return 0;
}