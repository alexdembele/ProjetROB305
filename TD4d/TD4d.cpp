#include <iostream>
#include <thread>
#include "../inc/Fifo.hpp"

const int MAX_NUM = 100; // Nombre maximum d'éléments à produire

// Fonction pour la tâche productrice
void producerTask(Fifo<int>& fifo, int id) 
{
    for (int i = 0; i < MAX_NUM; ++i) 
    {
        fifo.push(i);
        std::cout << "Producer " << id << " produced: " << i << std::endl;
    }
}

// Fonction pour la tâche consommatrice
void consumerTask(Fifo<int>& fifo, int id, bool* received) 
{
    for (int i = 0; i < MAX_NUM; ++i) 
    {
        int element = fifo.pop(1000);
        std::cout << "Consumer " << id << " received: " << element << std::endl;
        received[element] = true;
    }
}

int main() 
{
    Fifo<int> fifo;
    const int numProducers = 3; // Nombre de tâches productrices
    const int numConsumers = 2; // Nombre de tâches consommatrices
    bool received[MAX_NUM] = {false}; // Tableau pour vérifier la réception des éléments

    // Création des tâches productrices
    std::thread producers[numProducers];
    for (int i = 0; i < numProducers; ++i) 
    {
        producers[i] = std::thread(producerTask, std::ref(fifo), i);
    }

    // Création des tâches consommatrices
    std::thread consumers[numConsumers];
    for (int i = 0; i < numConsumers; ++i) 
    {
        consumers[i] = std::thread(consumerTask, std::ref(fifo), i, received);
    }

    // Attente de la fin des tâches productrices
    for (int i = 0; i < numProducers; ++i) 
    {
        producers[i].join();
    }

    // Attente de la fin des tâches consommatrices
    for (int i = 0; i < numConsumers; ++i) 
    {
        consumers[i].join();
    }

    // Vérification que tous les éléments ont été reçus
    bool allReceived = true;
    for (int i = 0; i < MAX_NUM; ++i) 
    {
        if (!received[i]) 
        {
            std::cout << "Element " << i << " was not received!" << std::endl;
            allReceived = false;
        }
    }

    if (allReceived) 
    {
        std::cout << "All elements were received successfully!" << std::endl;
    }

    return 0;
}
