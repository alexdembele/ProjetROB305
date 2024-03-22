#include <time.h>
#include <signal.h>
#include <thread>
#include <chrono>
#include <cstring>
#include <iostream>
#include "../inc/cpuLoop.h"
#include "../inc/timespec.h"
#include "../inc/Chrono.h"

int main()
{
    std::cout << "Calibration" <<std::endl;
    Calibrator myCalibration(200,10);
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "Fin de la calibration" <<std::endl;
    std::cout << "Nombre de Loop : " <<myCalibration.nLoops(3000) <<std::endl;
    
    CpuLoop myLoop(myCalibration);
    double duration = 3000;
    std::cout << "Execution d'un calcul pendant : " << duration << "ms"<<std::endl;
    Chrono myChrono;
    myLoop.runTime(duration);
    double temps=myChrono.lap();
    std::cout << "Fin du calcul en " << temps<<"ms"<<std::endl;
    return 0;
}