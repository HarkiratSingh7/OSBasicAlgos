// Dining Philosphers Problem Solution
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <functional>
#include "monitor.h"
#include <mutex>

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
Condition *conditions[TOTAL];
Semaphore cout_lock{1};

void CoutFunction(function<void()> cust_print)
{
    cout_lock.wait();
    cust_print();
    cout_lock.signal();
}

void test(int i)
{
    if (states[i] == HUNGRY && states[(i + TOTAL - 1) % TOTAL] != EATING && states[(i + 1) % TOTAL] != EATING)
    {
        states[i] = EATING;
        CoutFunction(
            [&]()
            {
                cout << i + 1 << ": Eating...\n";
            });
        conditions[i]->signal();
    }
}

void Pickup(int i)
{
    states[i] = HUNGRY;
    CoutFunction(
        [&]()
        {
            cout << i + 1 << ": Hungry and looking for chopsticks\n";
        });
    test(i);
    if (states[i] != EATING)
    {
        conditions[i]->wait();
    }
}

void PutDown(int i)
{
    states[i] = THINKING;

    CoutFunction(
        [&]()
        {
            cout << i + 1 << ": chopsticks are down now\n";
            cout << i + 1 << ": Thinking\n";
        });

    test((i + TOTAL - 1) % TOTAL);
    test((i + 1) % TOTAL);
}

void GenericPhilosopher(int i)
{
    while (true)
    {
        my_monitor.RunFunction(
            [&]()
            {
                Pickup(i);
            });

        my_monitor.RunFunction(
            [&]()
            {
                PutDown(i);
            });
    }
}

int main()
{
    ios::sync_with_stdio(false), cout.tie(nullptr);

    cout << "Press C or c and then Enter to terminate. Also execute from another console so that its output can be read after termination" << endl;
    cout << "Press enter to start" << endl;
    cin.get();

    for (auto &s : states)
        s = THINKING;

    for (int i = 0; i < TOTAL; i++)
    {
        conditions[i] = new Condition(&my_monitor);
    }

    {
        vector<thread> thread_pool(TOTAL);

        cout << "Size of thread pool is " << thread_pool.size() << endl;
        for (int i = 0; i < TOTAL; i++)
        {
            CoutFunction(
                [&]()
                {
                    cout << "Philosopher " << i + 1 << " has joined the dining table\n";
                });
            thread_pool[i] = thread(GenericPhilosopher, i);
        }

        while (true)
        {
            char c;
            cin.get(c);
            if (c == 'c' || c == 'C')
                break;
        }
    }

    for (int i = 0; i < TOTAL; i++)
        delete conditions[i];

    cout << "Bye Bye" << endl;

    return 0;
}
