#ifndef ANALYSER_H
#define ANALYSER_H

#include <atomic>
#include "chart.h"


class Analyser
{
public:
    Analyser(ChartView *c);
    ~Analyser();

    void AnalysisStart(int threads, int maxJobSize);
    void managerThread(int threads, int maxJobSize);

    void processManagerThread(int threads, int maxJobSize);

    void threadManagerThread(int threads, int maxJobSize);
    void singleThread(int jobSize);

    bool checkPrime(int number);

private:


    ChartView *chartView;

};

#endif // ANALYSER_H
