// Dining Philosphers
#include <iostream>
#include <vector>
#include <mutex>
#include <string>
#include <thread>
#include <functional>
#include "monitor.h"

using namespace std;

// Structures for the solution

const int TOTAL = 5;
enum
{
    THINKING,
    HUNGRY,
    EATING,
} states[TOTAL];

Monitor my_monitor;
mutex cout_mutex;
// vector<Condition> conditions(TOTAL, Condition(&my_monitor))
Condition *conditions[TOTAL];

void test(int i)
{
    if (states[i] == HUNGRY && states[(i + TOTAL - 1) % TOTAL] != EATING && states[(i + 1) % TOTAL] != EATING)
    {
        states[i] = EATING;
        conditions[i]->signal();
    }
}

void Pickup(int i)
{
    states[i] = HUNGRY;
    test(i);
    // my_monitor.RunFunction([&]()
    //                        { test(i); });
    if (states[i] != EATING)
    {
        conditions[i]->wait();
    }
}

void PutDown(int i)
{
    states[i] = THINKING;
    test((i + TOTAL - 1) % TOTAL);
    test((i + 1) % TOTAL);
    // my_monitor.RunFunction([&]()
    //                        { test((i + TOTAL - 1) % TOTAL); });

    // my_monitor.RunFunction([&]()
    //                        { test((i + 1) % TOTAL); });
}

void GenericPhilosopher(int i)
{
    while (true)
    {
        cout_mutex.lock();
        cout << i + 1 << ": Thinking..." << endl;
        cout_mutex.unlock();

        my_monitor.RunFunction([&]()
                               {
                                   cout_mutex.lock();
                                   cout << i + 1 << ": looking for chopsticks\n";
                                   cout_mutex.unlock();

                                   Pickup(i);

                                   cout_mutex.lock();
                                   cout << i + 1 << ": eating...\n"
                                        << endl;
                                   cout_mutex.unlock();
                               });
        my_monitor.RunFunction([&]()
                               {
                                   cout_mutex.lock();
                                   cout << i + 1 << ": going to put down the chopsticks\n"
                                        << endl;
                                   cout_mutex.unlock();

                                   PutDown(i);

                                   cout_mutex.lock();
                                   cout << i + 1 << ": chopsticks are down now;" << endl;
                                   cout_mutex.unlock();
                               });
    }
}

int main()
{
    for (auto &s : states)
        s = THINKING;

    for (int i = 0; i < TOTAL; i++)
    {
        conditions[i] = new Condition(&my_monitor);
    }

    {
        vector<thread> thread_pool(TOTAL);

        for (int i = 0; i < TOTAL; i++)
        {
            cout_mutex.lock();
            cout << "Philosopher " << i + 1 << " has joined the dining table" << endl;
            cout_mutex.unlock();
            thread_pool.push_back(thread(GenericPhilosopher, i));
        }

        cout_mutex.lock();
        cout << "Size of thread pool is " << TOTAL << endl;
        cout_mutex.unlock();

        cout_mutex.lock();
        cout << "Enter exit to exit the threads: " << endl;
        cout_mutex.unlock();

        while (true)
        {
            string inp;
            // cin >> inp;
            if (inp == "exit")
            {
                break;
            }
            else
            {
                //     cout_mutex.lock();
                //     cout << "Enter exit to exit the threads: ";
                //     cout_mutex.unlock();
            }
        }
    }

    for (int i = 0; i < TOTAL; i++)
        delete conditions[i];

    cout << "Bye Bye" << endl;

    return 0;
}