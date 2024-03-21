#include <cstring>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <pthread.h>
#include <vector>
#include <climits>
#include "../inc/timespec.h"

struct Data 
{
    volatile double  counter;
    unsigned long nLoops;  
    bool pStop;  
    double duration_ms;
};

// =========================================
// Fonctions du compteur
// =========================================
void incr(unsigned long nLoops, double* pCounter,bool* pStop)
{
    for (unsigned long u = 0; u < nLoops; u++)
    {
        if (*pStop)
        {  
           break; 
        } 
        *pCounter += 1;
    }
}

void* call_incr(void* v_data)
{
    Data* p_data = (Data*) v_data;
    incr(p_data->nLoops, (double *)&p_data->counter,&p_data->pStop);
    return v_data;
}

// =========================================
// Fonctions du timer
// =========================================
void timer(bool* pStop,double* duration_ms)
{
    timespec_wait(timespec_from_ms(*duration_ms));
   *pStop =true;
}

void* call_timer(void* v_data)
{
    Data* p_data = (Data*) v_data;
    timer(&p_data->pStop, &p_data->duration_ms);
    return v_data;
}



void calib1(double* temps_exec, double* nombreLoops, double duration_ms)
{
    unsigned long nLoops = (unsigned long)UINT_MAX;
    bool pStop = false;
    pthread_t incrementThread;
    pthread_t timerThread;
    //premiere mesure
    std::cout << "Mesure pour un temps de "<< duration_ms<<"ms"<<std::endl;
    Data data = {  0.0 , nLoops,pStop,duration_ms};
    timespec debut = timespec_now();
   
    pthread_create(&incrementThread, nullptr, call_incr, &data);
    pthread_create(&timerThread, nullptr, call_timer, &data);

    pthread_join(incrementThread, nullptr);
    pthread_join(timerThread, nullptr);

    timespec fin = timespec_now();
    timespec duree =fin-debut;
    *temps_exec = timespec_to_ms(duree);
    *nombreLoops = data.counter;
}
// =========================================
// Classe Fonction utiles pour la regression linéaire
// =========================================

// Fonction pour calculer la moyenne d'un vecteur de doubles
double mean(const std::vector<double>& data) 
{
    double sum = 0.0;
    for (const auto& value : data) 
    {
        sum += value;
    }
    return sum / data.size();
}

// Fonction pour calculer la covariance entre deux vecteurs de doubles
double covariance(const std::vector<double>& x, const std::vector<double>& y) 
{
    double sum = 0.0;
    double mean_x = mean(x);
    double mean_y = mean(y);

    for (size_t i = 0; i < x.size(); ++i) 
    {
        sum += (x[i] - mean_x) * (y[i] - mean_y);
    }
    return sum / x.size();
}

// Fonction pour calculer la pente (coefficient angulaire) d'une régression linéaire
double slope(const std::vector<double>& x, const std::vector<double>& y) 
{
    double cov_xy = covariance(x, y);
    double var_x = covariance(x, x);

    return cov_xy / var_x;
}

// Fonction pour calculer l'ordonnée à l'origine d'une régression linéaire
double intercept(const std::vector<double>& x, const std::vector<double>& y) 
{
    double mean_x = mean(x);
    double mean_y = mean(y);

    return mean_y - slope(x, y) * mean_x;
}


int main()
{
    std::vector<double> x = {}; //echantillon de temps
    std::vector<double> y = {}; //echantillon de nLoops
    double temps_exec,nombreLoops;
    double a,b;
    for(double i =1000; i<=10000 ;i+=1000)
    {
        calib1(&temps_exec,&nombreLoops,i);
        x.push_back(temps_exec);
        y.push_back(nombreLoops);
    }
    std::cout << "Calcul des coefficients" << std::endl;
    a = slope(x, y); // Pente
    b = intercept(x, y); // Ordonnée à l'origine

    std::cout << "Valeur des coefficients de la droite l(t) = a*t +b : a  =" << a << " ; b = "<< b<<std::endl;
    std::cout << "Test des valeurs  pour une durée de 5s : "<<std::endl;
    unsigned int nLoops = (unsigned int ) a * 5000 + b;
    std::cout << "nLoops =  "<<nLoops <<std::endl;
    Data data = {  0.0 , nLoops,false,10000};
    pthread_t incrementThread;
    timespec debut = timespec_now();
   
    pthread_create(&incrementThread, nullptr, call_incr, &data);
    pthread_join(incrementThread, nullptr);
    timespec fin = timespec_now();
    timespec duree =fin-debut;
    temps_exec = timespec_to_ms(duree);
    std::cout << "Temps d'execution : "<< temps_exec <<"ms" <<std::endl;
    std::cout << "Valeur du compteur : "<< data.counter <<"ms" <<std::endl;



    return 0 ;
}