//
// Created by zhang on 14/01/17.
//
#include <stdio.h>
#include "job.h"
void printJob(Job* job)
{
    printf("**********  Job %d ***********\n", job->id);
    printf("Weight: %d\n", job->w);
    int i;
    for (i = 0; i < NB_MACHINES; i++)
    {
        printf("Processing time on machine %d: %d \n", i, job->pt[i]);
    }

    for (i = 0; i < NB_MACHINES; i++)
    {
        printf("Start time on machine %d: %d \n", i, job->start[i]);
    }
    printf("**********  End  ***********\n");
}


char* toStringJob(Job* job, char* str1)
{
    /*
     * not a good way
     */
     sprintf(str1,
             "%d %d %d %d %d %d %d %d %d %d\n",
             job->id, job->w,
             job->pt[0], job->pt[1], job->pt[2], job->pt[3],
             job->start[0], job->start[1], job->start[2], job->start[3]);
    return str1;
}

int getLatestEndTime(Job* job)
{
    int max_end_time = 0;
    for (int i = 0; i < NB_MACHINES; i++)
    {
        int endTime = job->start[i] + job->pt[i];
        if (endTime > max_end_time)
        {
            max_end_time = endTime;
        }
    }
    return max_end_time;
}