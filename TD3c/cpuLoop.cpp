#include <iostream>
#include <time.h>
#include "../inc/cpuLoop.hpp"
#include "../inc/timespec.hpp"


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

// =========================================
// Classe Calibrator
// =========================================

Calibrator::Calibrator(double samplingPeriod_ms,unsigned int nSamples) : myLooper()
{
    //Créer Looper et dix mesures intervalle 1s
    samples={};
    period = samplingPeriod_ms;
    nPoint = nSamples;

    startPeriodic(period);
    myLooper.runLoop();
    stop();

}

void Calibrator::callback()
{
    samples.push_back(myLooper.getSample());
    if ((unsigned int)samples.size()>=nPoint)
    {
        myLooper.stopLoop();
        //regression linéaire
        std::vector<double> x = {};
        for(double t=1; t<=nPoint;t+=1)
        {
            x.push_back(t*period);
        }
        a = slope(x, samples); // Pente
        b = intercept(x, samples); // Ordonnée à l'origine
    }    
}

double Calibrator::nLoops(double duration_ms)
{
    double n_Boucle=a*duration_ms+b;

    return n_Boucle;
}
// =========================================
// Classe Looper
// =========================================
double Looper::runLoop(double nLoops)
{
    doStop = false; 
    iLoop = 0; 
    while (iLoop < nLoops && !doStop) 
    {
        iLoop++; 
    }
    return iLoop; 
}

double Looper::getSample()
{
    return iLoop;
}

double Looper::stopLoop()
{
    doStop = true; 
    return iLoop; 
}

CpuLoop::CpuLoop(Calibrator& calibrator) : myCalibrator(calibrator)
{

}

void CpuLoop::runTime(double duration_ms)
{
    double n = myCalibrator.nLoops(duration_ms);
    runLoop(n);
}




