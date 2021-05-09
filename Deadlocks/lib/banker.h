#ifndef BANKER_H
#define BANKER_H

#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

#define INT_DISP_LENGTH 17

struct Process
{
    int id;
    std::vector<int> maximum;
    std::vector<int> allocated;
    const int need(int resType) const
    {
        return maximum[resType] - allocated[resType];
    }
    bool finished = false;
};

class ResourceManager
{
public:
    ResourceManager(int mResourceTypes, int nProcesses, std::vector<int> AvailableResourceList, std::vector<Process> stateProcesses) : n(nProcesses),
                                                                                                                                       m(mResourceTypes),
                                                                                                                                       Resources(AvailableResourceList),
                                                                                                                                       Processes(stateProcesses)
    {
    }

    bool requestResource(int procId)
    {
        Process *Proc;
        for (auto &tmp : (Processes))
        {
            if (tmp.id == procId)
            {
                Proc = &tmp;
                break;
            }
        }
        for (int id = 0; id < m; id++)
        {
            if (Proc->need(id) < 0)
                throw std::string("Exceeds maximum claim");
        }

        bool good = true;
        for (int id = 0; id < m; id++)
        {
            if (Proc->need(id) <= Resources[id])
                continue;
            good = false;
            break;
        }

        if (good)
        {
            auto CopyReses = Resources;
            auto CopyAllocs = Proc->allocated;
            for (int id = 0; id < m; id++)
            {
                if (Proc->need(id) == 0)
                    continue;

                Resources[id] -= Proc->need(id);
                Proc->allocated[id] += Proc->need(id);
            }
            // if (!isSafeState())
            // {
            //     Resources = CopyReses;
            //     Proc->allocated = CopyAllocs;
            //     return false;
            // }
            return true;
        }

        return false;
    }

    bool SafeStateMethod(std::vector<int>& Sequence)
    {
        auto Work = Resources;
        std::vector<bool> Finish(n, false);

        bool exists = true;
        int i = 0;
        while (exists)
        {
            if (i == n)
                i = 0;
            exists = false;
            for (; i < n; i++)
            {
                if (Finish[i] == false)
                {
                    auto &Proc = (Processes)[i];
                    bool allLess = true;
                    for (int id = 0; id < m; id++)
                    {
                        if (Proc.maximum[id] == 0)
                            continue;
                        if (Proc.need(id) <= Work[id])
                        {
                            // exists = true;
                            // break;
                            continue;
                        }
                        allLess = false;
                        break;
                    }
                    if (allLess)
                        exists = true;
                    if (exists)
                        break;
                }
            }
            if (exists)
            {
                for (int id = 0; id < m; id++)
                {
                    Work[id] += (Processes)[i].allocated[id];
                }
                Finish[i] = true;
                Sequence.push_back(i);
                ++i;
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (Finish[i] == false)
                return false;
        }

        return true;
    }

private:
    int n, m;
    std::vector<int> Resources;
    std::vector<Process> Processes;
};

#endif