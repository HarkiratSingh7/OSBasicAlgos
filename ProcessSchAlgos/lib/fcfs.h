#ifndef FCFS_H
#define FCFS_H

#include <iostream>
#include <queue>
#include <iomanip>

#define INT_DISP_LENGTH 17

struct ProcessCharacteristics
{
    unsigned int id;
    unsigned int msBurstTime;
    unsigned int waitTime {0};
    unsigned int turnAroundTime{0};
};

void runScheduler(std::deque<ProcessCharacteristics> readyQueue)
{
    using namespace std;

    cout << "Total Number of process received are :"<<readyQueue.size()<<'\n';
    cout << "Before starting the algorithm the process details are:\n";
    cout << setw(INT_DISP_LENGTH) << "PROCESS ID" << setw(INT_DISP_LENGTH) << "BURST TIME\n";
    for (auto& itr : readyQueue)
    {
        cout << setw(INT_DISP_LENGTH) << itr.id << setw(INT_DISP_LENGTH)<<itr.msBurstTime<<'\n';   
    }

    vector<ProcessCharacteristics> ProcessRecords;

    unsigned int msTime {0};
    double waitTime{0};
    while (!readyQueue.empty())
    {
        ProcessCharacteristics process = readyQueue.front();
        readyQueue.pop_front();

        // Add waiting time 
        process.waitTime = msTime;
        waitTime += process.waitTime;
        msTime += process.msBurstTime;

        // Add Turnaround Time - How much it took for the system to process it starting from 1st proc
        process.turnAroundTime = msTime; 

        ProcessRecords.push_back(process);
    }

    cout << setw(INT_DISP_LENGTH) << "PROCESS ID" << setw(INT_DISP_LENGTH) << "WAITING TIME" << setw(INT_DISP_LENGTH) << "BURST TIME"<<setw(INT_DISP_LENGTH)<<"TURNAROUND TIME"<<"\n";
    for (auto& process : ProcessRecords)
    {
        cout << setw(INT_DISP_LENGTH) << process.id << setw(INT_DISP_LENGTH) << process.waitTime << setw(INT_DISP_LENGTH) << process.msBurstTime<<setw(INT_DISP_LENGTH)<<process.turnAroundTime<<"\n";
    }

    cout << "The Average Waiting Time is " << waitTime / ProcessRecords.size() << '\n';
}
#endif // !FCFS_H
