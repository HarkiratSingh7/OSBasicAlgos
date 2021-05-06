#include <iostream>
#include "fcfs.h"

using namespace std;

int main()
{
    deque<ProcessCharacteristics> Processes;
    int n;
    cout << "Number of Processes: ";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        ProcessCharacteristics AProcess;
        AProcess.id = i; // Computer assigns the id to the process

        cout << "Enter the burst time for process "<<i<<": ";
        cin >> AProcess.msBurstTime;
        Processes.push_back(AProcess);
    }
    
    cout << "Running the FCFS Algorithm\n";
    runScheduler(Processes);
}