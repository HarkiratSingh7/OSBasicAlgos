// Shortest Job First Scheduling
// or shortest next cpu burst algorithm

#ifndef SJFS_H
#define SJFS_H

#include <iostream>
#include <queue>
#include <iomanip>
#include <algorithm>

#define INT_DISP_LENGTH 17

struct SJFProcessCharacteristics
{
    unsigned int id;
    unsigned int msBurstTime;
    unsigned int waitTime{0};
    unsigned int turnAroundTime{0};
};

bool sortFunction(const SJFProcessCharacteristics &p1, const SJFProcessCharacteristics &p2)
{
    if (p1.msBurstTime > p2.msBurstTime)
        return false;
    return true;
}

void runScheduler(std::vector<SJFProcessCharacteristics> jobList)
{
    using namespace std;

    cout << "Total Number of process received are :" << jobList.size() << '\n';
    cout << "Before starting the algorithm the process details are:\n";
    cout << setw(INT_DISP_LENGTH) << "PROCESS ID" << setw(INT_DISP_LENGTH) << "BURST TIME\n";
    for (auto &itr : jobList)
    {
        cout << setw(INT_DISP_LENGTH) << itr.id << setw(INT_DISP_LENGTH) << itr.msBurstTime << '\n';
    }

    sort(jobList.begin(), jobList.end(), sortFunction);

    vector<SJFProcessCharacteristics> ProcessRecords;

    unsigned msTime{0};
    double waitTime{0};
    for (int i = 0; i < jobList.size(); i++)
    {
        SJFProcessCharacteristics process = jobList[i];

        // Add waiting time
        process.waitTime = msTime;
        waitTime += process.waitTime;
        msTime += process.msBurstTime;

        // Add Turnaround Time - How much it took for the system to process it starting from 1st proc
        process.turnAroundTime = msTime;

        ProcessRecords.push_back(process);
    }

    cout << setw(INT_DISP_LENGTH) << "PROCESS ID" << setw(INT_DISP_LENGTH) << "WAITING TIME" << setw(INT_DISP_LENGTH) << "BURST TIME" << setw(INT_DISP_LENGTH) << "TURNAROUND TIME"
         << "\n";
    for (auto &process : ProcessRecords)
    {
        cout << setw(INT_DISP_LENGTH) << process.id << setw(INT_DISP_LENGTH) << process.waitTime << setw(INT_DISP_LENGTH) << process.msBurstTime << setw(INT_DISP_LENGTH) << process.turnAroundTime << "\n";
    }

    cout << "The Average Waiting Time is " << waitTime / ProcessRecords.size() << '\n';
}

#endif