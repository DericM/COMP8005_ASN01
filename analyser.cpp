#include "analyser.h"
#include "chart.h"
#include <thread>
#include <atomic>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <ctime>
#include <QDebug>
#include <mutex>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>




static std::atomic<int> tCurrentNumber;
std::mutex threadLock;


Analyser::Analyser(ChartView *c)
{
    chartView = c;
}

Analyser::~Analyser()
{
    //delete chartView;
}

void Analyser::AnalysisStart(int threads, int maxJobSize){
    std::thread(&Analyser::managerThread, this, threads, maxJobSize).detach();
}


void Analyser::managerThread(int threads, int maxJobSize){
    std::thread thread1(&Analyser::processManagerThread, this, threads, maxJobSize);
    thread1.join();

    //std::thread thread2(&Analyser::threadManagerThread, this, threads, maxJobSize);
    //thread2.join();
}

void Analyser::processManagerThread(int threads, int maxJobSize){

    std::clock_t start, end;
    double duration;

    int jobSize = 100000;


//    int pipefds[2*threads];

//    for(int i = 0; i < (threads); i++){
//        if(pipe(pipefds + i*2) < 0) {
//            exit(EXIT_FAILURE);
//        }
//    }

    while(jobSize < maxJobSize){

        int currentNumber = 0;

        int pids[threads];

        start = std::clock();



        for(int i=0 ; i<threads; i++) {
            pids[i] = fork();
            if(pids[i] == 0) {
                for(int j=0; j<jobSize; j++){
                    checkPrime(currentNumber);
                    currentNumber++;
                }
                return;
            }
        }
        int runingthreads = threads;
        while(runingthreads > 0){
            runingthreads = threads;
            for(int i=0; i<threads; i++){
                if(kill(pids[i], 0)==0){
                    runingthreads--;
                }
            }
        }

//        for(int i=0 ; i<threads; i++) {
//            if(fork() == 0) {
//                int pipe_w = pipefds[2*i+1];

//                int currentNumber = i;

//                while (currentNumber <= jobSize)
//                {
//                    checkPrime(currentNumber);
//                    currentNumber += threads;
//                }
//                write(pipe_w, &currentNumber, sizeof(currentNumber));
//                for(i = 0; i < 2 * threads; i++){
//                    close(pipefds[i]);
//                }
//                return;
//            }
//        }
//        int pipes_r[threads];
//        for(int i=0; i<threads; i++){
//            pipes_r[i] = pipefds[2*i];
//        }

//        int currentNumber = 0;
//        int runningThreads = threads;

//        while (runningThreads > 0){
//            for(int i=0; i<threads; i++){
//                read(pipes_r[i], &currentNumber, sizeof(currentNumber));
//                if(currentNumber > jobSize){
//                    runningThreads--;
//                    currentNumber = 0;
//                }
//            }
//        }

        end = std::clock();

        duration = 1000.0 * ( end - start ) / CLOCKS_PER_SEC;
        chartView->addProcessMarker(jobSize, duration);

        jobSize += 100000;
    }

//    for(int i = 0; i < 2 * threads; i++){
//        close(pipefds[i]);
//    }
}


void Analyser::threadManagerThread(int threads, int maxJobSize){
    std::clock_t start, end;
    double duration;

    int jobSize = 100000;

    while(jobSize <= maxJobSize){

        start = std::clock();

        std::thread threadsArray[threads];

        for(int i=0; i<threads; i++)
        {
            threadsArray[i] = std::thread(&Analyser::singleThread, this, jobSize);
        }
        for(int i=0; i<threads; i++)
        {
            threadsArray[i].join();
        }

        end = std::clock();

        duration = (1000.0) * ( end - start ) / CLOCKS_PER_SEC;
        chartView->addThreadMarker(jobSize, duration);

        jobSize += 100000;
    }

}




void Analyser::singleThread(int jobSize){
    int currentNumber = 0;

    while (currentNumber <= jobSize)
    {
        threadLock.lock();
        currentNumber = tCurrentNumber;
        tCurrentNumber++;
        threadLock.unlock();

        checkPrime(currentNumber);
    }

}



bool Analyser::checkPrime(int number){
    bool prime=true;
    for (int j=2; j*j<=number; j++)
    {
        if (number % j == 0)
        {
            prime=false;
            break;
        }
    }
    return prime;
}
