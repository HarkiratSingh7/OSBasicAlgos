#ifndef MONITOR_H
#define MONITOR_H

#include <functional>
#include <mutex>

class Monitor
{
public:
    void RunFunction(std::function<void()> func)
    {
        mmutex.lock();
        func();
        if (suspended_count > 0)
            next.unlock();
        else
            mmutex.unlock();
    }

private:
    std::mutex mmutex, next;
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
            mon->next.unlock();
        else
            mon->mmutex.unlock();
        lock.lock();
        --count;
    }

    void signal()
    {
        if (count > 0)
        {
            ++mon->suspended_count;
            lock.unlock();
            mon->next.lock();
            --mon->suspended_count;
        }
    }

private:
    std::mutex lock;
    int count{0};
    Monitor *mon;
};

#endif // !MONITOR_H
