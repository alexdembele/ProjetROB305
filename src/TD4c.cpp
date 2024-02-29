#include <time.h>
#include <signal.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <condition_variable>
#include "../inc/Mutex.hpp"
#include "../inc/timespec.hpp"






const int nProd = 5; // Nombre de tâches productrices
const int nCons = 5; // Nombre de tâches consommatrices
const int numTokens = 20; // Nombre total de jetons à créer

Semaphore sem(0); // Semaphore initialisé à vide

// Fonction pour la tâche productrice
void producerTask() {
    for (int i = 0; i < numTokens / nProd; ++i) 
    {
        sem.give(); // Ajoute un jeton
        std::cout<<"jeton donné : "<<i<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simule un traitement
    }
}

// Fonction pour la tâche consommatrice
void consumerTask() {
    for (int i = 0; i < numTokens / nCons; ++i) 
    {
        sem.take(); // Prend un jeton
        std::cout<<"jeton pris : "<<i<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simule un traitement
    }
}

int main() 
{
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // Création des tâches productrices
    for (int i = 0; i < nProd; ++i) 
    {
        producers.emplace_back(producerTask);
    }

    // Création des tâches consommatrices
    for (int i = 0; i < nCons; ++i) 
    {
        consumers.emplace_back(consumerTask);
    }

    // Attente de la fin des tâches productrices
    for (auto& producer : producers) 
    {
        producer.join();
    }

    // Attente de la fin des tâches consommatrices
    for (auto& consumer : consumers) 
    {
        consumer.join();
    }

    // Affichage du nombre de jetons restants 
    std::cout << "Nombre de jetons restants : " << sem.getCounter() << std::endl;

    return 0;
}