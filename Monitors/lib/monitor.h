#ifndef MONITOR_H
#define MONITOR_H

#include <functional>
#include <atomic>

class Spinlock
{
public:
    void lock()
    {
        while (_lock.exchange(true))
            ;
    }

    void unlock()
    {
        _lock.exchange(false);
    }

private:
    std::atomic<bool> _lock{false};
};

class Semaphore
{
public:
    Semaphore(int init_count)
        : counter(init_count)
    {
    }
    void wait()
    {
        int run = 0;
        while (!run)
        {
            inner_lock.lock();
            if (counter > 0)
            {
                counter--;
                run = 1;
            }
            inner_lock.unlock();
        }
    }

    void signal()
    {
        inner_lock.lock();
        counter++;
        inner_lock.unlock();
    }

private:
    Spinlock inner_lock;
    int counter{0};
};

class Monitor
{
public:
    void RunFunction(std::function<void()> func)
    {
        mmutex.wait();
        func();
        if (suspended_count > 0)
            next.signal();
        else
            mmutex.signal();
    }

private:
    Semaphore mmutex {1};
    Semaphore next{0};
    int suspended_count{0};
    friend class Condition;
};

class Condition
{

public:
    Condition(const Condition &) = delete;
    Condition(Monitor *parent_mon)
    {
        mon = parent_mon;
    }
    void wait()
    {
        ++count;
        if (mon->suspended_count > 0)
            mon->next.signal();
        else
            mon->mmutex.signal();
        lock.wait();
        --count;
    }

    void signal()
    {
        if (count > 0)
        {
            ++mon->suspended_count;
            lock.signal();
            mon->next.wait();
            --mon->suspended_count;
        }
    }

private:
    Semaphore lock{0};
    int count{0};
    Monitor *mon;
};

#endif // !MONITOR_H
