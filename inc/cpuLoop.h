#ifndef Looper_h_INCLUDED
#define Looper_h_INCLUDED

#include <time.h>
#include <signal.h>
#include <iostream>
#include "../inc/timespec.h"
#include "../inc/Timer.h"

class Calibrator;
class Looper
{
    private:
        volatile bool doStop;
        double iLoop;
    public:
        Looper() : doStop(false), iLoop(0) {};
        double runLoop(double nLoops=DBL_MAX);
        double getSample();
        double stopLoop();
};

class CpuLoop : public Looper
{
    private:
        Calibrator& myCalibrator;
    public:

        CpuLoop(Calibrator& calibrator);
        void runTime(double duration_ms);

};

class Calibrator : public PeriodicTimer
{
    private:
        double a;
        double b;
        double period;
        unsigned int  nPoint;
        std::vector<double> samples;
        Looper myLooper;
    protected:
        virtual void callback() override;
    public:
        Calibrator(double samplingPeriod_ms,unsigned int nSamples);
        double nLoops(double duration_ms);
};
#endif