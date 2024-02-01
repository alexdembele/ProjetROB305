#include <time.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <cstring>
#include <iostream>
#include <pthread.h>

void* incrementer(void* v_stop)
{
    volatile bool* p_stop = (volatile bool*) v_stop;
    double counter = 0.0;
    while (! (*p_stop)) 
    {
        counter += 1.0;
    }
    std::cout << "Counter value = " << counter << std::endl;
    return v_stop;
}

int main(int argc, char* argv[])
{
    volatile bool stop = false;
    pthread_t incrementThread;

    pthread_create(&incrementThread, nullptr, incrementer, (void*) &stop); 
    std::cout << "Type 's' to stop: " << std::flush;
    stop = true;
    return 0;
}