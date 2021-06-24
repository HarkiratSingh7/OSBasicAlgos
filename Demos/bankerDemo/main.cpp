#include <iostream>
#include <iomanip>
#include "banker.h"

using namespace std;

const int COLUMN = 10;

void PrintProcessStateTable(const vector<Process> &Processes, int M, const vector<int> &Resources)
{
    cout << '\n';
    cout << setw(COLUMN) << "PID";
    for (int i = 0; i < M; i++)
    {
        string a("ALLOC_");
        a.push_back(i+'0');
        cout << setw(COLUMN) << a;
    }
    for (int i = 0; i < M; i++)
    {
        string a("MAX_");
        a.push_back(i+'0');
        cout << setw(COLUMN) << a;
    }
    for (int i = 0; i < M; i++)
    {
        string a("NEED_");
        a.push_back(i+'0');
        cout << setw(COLUMN) << a;
    }
    cout << '\n';
    for (auto &proc : Processes)
    {
        cout << setw(COLUMN) << proc.id;
        for (int i = 0; i < M; i++)
        {
            cout << setw(COLUMN) << proc.allocated[i];
        }
        for (int i = 0; i < M; i++)
        {
            cout << setw(COLUMN) << proc.maximum[i];
        }
        for (int i = 0; i < M; i++)
        {
            cout << setw(COLUMN) << proc.need(i);
        }
        cout << '\n';
    }
    cout << "AVAILABLE\n";
    for (int i = 0; i < M; i++)
    {
        cout << setw(COLUMN) << i << setw(COLUMN) << Resources[i] << " \n";
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false); // Useful, copy paste whole input data at once for testing

    int m;
    cout << "Please enter types of Resources: ";
    cin >> m;
    vector<int> Resources(m, 0);
    for (int id = 0; id < m; id++)
    {
        cout << "How many instances are of Resource " << id << " (id): ";
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
        cout << "For process with id " << id << '\n';
        cout << "Please enter following details\n";
        for (int resId = 0; resId < m; resId++)
        {
            cout << "Maximum of Resource Type - " << resId << ": ";
            int temp;
            cin >> temp;
            proc.maximum.push_back(temp);

            cout << "Allocated of Resource Type - " << resId << ": ";
            cin >> temp;
            proc.allocated.push_back(temp);
            Resources[resId] -= temp;
        }
        Processes.push_back(proc);
    }

    ResourceManager rsMgr(m, n, Resources, Processes);

    PrintProcessStateTable(Processes, m, Resources);

    int count = 0;
    vector<int> Sequence;
    rsMgr.SafeStateMethod(Sequence);
    cout << "This is the order in which processes might go (there can be more)\n";
    for (auto &item : Sequence)
    {
        cout << item << ", ";
    }

    cout << "\nWould you like to make request tests for the provided state? (only y for yes)";
    char ans;
    cin >> ans;
    if (ans == 'y')
    {
        cout << "Would you like to allocate resources if tests are successful? (only y for yes) (Recommended, enter y)";
        cout << "\nIf y is entered process state table would be updated and displayed.\nANS: ";
        bool test = true;
        cin >> ans;
        if (ans == 'y')
            test = false;
        ans = 'y';
        while (ans == 'y')
        {
            cout << "Enter the process id that should make request ";
            int pid;
            cin >> pid;
            vector<int> Requests;
            for (int i = 0; i < m; i++)
            {
                cout << "Request for resource " << i << ": ";
                int r;
                cin >> r;
                Requests.push_back(r);
            }
            if (test)
                cout << "Note: This is only running as a test. And tests are assumed that they won't allocate\n";
            try
            {
                auto val = rsMgr.requestResource(pid, Requests, test);

                if (val.second)
                {
                    Resources = val.first; // Update Resources
                    cout << "\nRequest would result in safe state.\n";
                }
                else
                {
                    cout << "\nRequest would result in UNSAFE state.\n";
                }
            }
            catch (std::string s)
            {
                cout << s << '\n';
            }
            if (!test)
            {
                vector<int> Sequence;
                rsMgr.SafeStateMethod(Sequence);
                cout << "This is the order in which processes might go (there can be more)\n";
                for (auto &item : Sequence)
                {
                    cout << item << ", ";
                }
                PrintProcessStateTable(Processes, m, Resources);
            }
            cout << "Would you like to continue testing? (only y for yes)";
            cin >> ans;
        }
    }

    cout << endl;

    return 0;
}
