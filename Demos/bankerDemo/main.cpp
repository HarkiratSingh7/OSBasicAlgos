#include <iostream>
#include "banker.h"

using namespace std;

int main()
{
    int m;
    cout << "Please enter types of Resources: ";
    cin >> m;
    vector<int> Resources(m, 0);
    for (int id = 0; id < m; id++)
    {
        cout << "How many types are of Resource "<<id<<" (id): ";
        cin >> Resources[id];
    }

    int n;
    cout << "How many processes have to be run? : ";
    cin >> n;
    vector<Process> Processes;
    for (int id = 0; id < n; id++)
    {
        Process proc;
        proc.id = id;
        cout << "For process with id "<<id<<'\n';
        cout <<"Please enter following details\n";
        for (int resId = 0; resId < m; resId ++)
        {
            cout << "Maximum of Resource Type - "<<resId<<": ";
            int temp; cin >> temp; 
            proc.maximum.push_back(temp);

            cout << "Allocated of Resource Type - "<<resId<<": ";
            cin >> temp; 
            proc.allocated.push_back(temp);
            Resources[resId] -= temp;
        }
        Processes.push_back(proc);
    }

    ResourceManager rsMgr(m, n, Resources, Processes);
    int count = 0;
    vector<int> Sequence;
    rsMgr.SafeStateMethod(Sequence);
    // while (count != n)
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         if (!Processes[i].finished)
    //         rsMgr.isSafeState(Sequence);
    //     }
    // }

    for (auto& item : Sequence)
    {
        cout << item << ", ";
    }

    cout << endl;

    return 0;

}