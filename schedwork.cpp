#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;
typedef std::vector<std::vector<Worker_T>> DailySchedule;
typedef std::vector<std::vector<bool>> AvailabilityMatrix;

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if (avail.empty()) {
        return false;
    }
    else if (avail.size() == sched.size() && sched.back()[dailyNeed - 1] != INVALID_ID) {
        return true;
    }

    if (sched.empty() || sched.back()[dailyNeed - 1] != INVALID_ID) {
        vector<Worker_T> toInsert(dailyNeed + 1, INVALID_ID);
        toInsert[dailyNeed] = 0;
        sched.push_back(toInsert);
    }

    size_t day = sched.size() - 1;
    vector<Worker_T> currentDaySchedule = sched[day];
    int nextWorkerIndex = currentDaySchedule[dailyNeed];
    size_t daySize = avail[day].size();

    for (size_t j = 0; j < daySize; ++j) 
    {
        if (!avail[day][j]) continue;

        size_t shiftCount = 0;
        bool isAlreadyScheduled = false;

        for (size_t currentDay = 0; currentDay <= day; currentDay++) 
        {
            for (size_t shiftIndex = 0; shiftIndex < dailyNeed; shiftIndex++) 
            {
                if (sched[currentDay][shiftIndex] == j) 
                {
                    if (currentDay == day) 
                    {
                        isAlreadyScheduled = true;
                        break;
                    }
                    shiftCount++;
                    if (shiftCount >= maxShifts) 
                    {
                        isAlreadyScheduled = true;
                        break;
                    }
                }
            }
            if (isAlreadyScheduled) break;
        }

        if (isAlreadyScheduled) continue;

        currentDaySchedule[nextWorkerIndex] = j;
        currentDaySchedule[dailyNeed]++;

        sched[day] = currentDaySchedule;
        if (schedule(avail, dailyNeed, maxShifts, sched)) {
            if (nextWorkerIndex == 0) {
                sched[day].pop_back();
            }
            return true;
        }

        currentDaySchedule[nextWorkerIndex] = INVALID_ID;
        currentDaySchedule[dailyNeed]--;
        sched[day] = currentDaySchedule;
    }

    if (sched[day][0] == INVALID_ID) {
        sched.pop_back();
    }

    return false;
}
    