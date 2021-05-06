#include <iostream>
#include "sjfs.h"

using namespace std;

int main()
{
    vector<SJFProcessCharacteristics> Processes;
    int n;
    cout << "Number of Processes: ";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        SJFProcessCharacteristics AProcess;
        AProcess.id = i; // Computer assigns the id to the process

        cout << "Enter the burst time for process " << i << ": ";
        cin >> AProcess.msBurstTime;
        Processes.push_back(AProcess);
    }

    cout << "Running the FCFS Algorithm\n";
    runScheduler(Processes);
}