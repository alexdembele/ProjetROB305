#include <time.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../inc/timespec.hpp"

#define INTERVAL_MS 500 // 2 Hz en microsecondes

volatile int counter = 0;

void timer_handler(int signum, siginfo_t *info, void *context) 
{
    if (counter < 15) 
    {
        printf("Compteur : %d\n", ++counter);
    } 

    else 
    {
        printf("Fin du programme.\n");
        exit(EXIT_SUCCESS);
    }
}

int main()
{
    struct sigaction sa;
    struct sigevent sev;
    timer_t timerid;
    struct itimerspec its;
    //struct timespec ts;

    // Configurer le gestionnaire de signal pour SIGALRM
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timer_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) == -1) 
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Créer le timer POSIX
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGALRM;
    sev.sigev_value.sival_ptr = &timerid;
    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1)
    {
        perror("timer_create");
        exit(EXIT_FAILURE);
    }

    // Configurer l'intervalle du timer
    
    its.it_value = timespec_from_ms(INTERVAL_MS);
    its.it_interval = timespec_from_ms(INTERVAL_MS);
    

    if (timer_settime(timerid, 0, &its, NULL) == -1) 
    {
        perror("timer_settime");
        exit(EXIT_FAILURE);
    }

    // Attendre jusqu'à la fin du timer
    while (1) 
    {
        pause();
    }
    return 0;
}