//
// Created by zhang on 14/01/17.
//

#include "heuristiqueErkang.h"


void heuristiqueErkang(Job** jobs, int nbJobs)
{
    /*
     * result: 2d-array of [NB_MACHINES][NB_JOBS]
     * Each row stands for a scheduling sequence for a machine
     * Initialisation with 0 values
     */
    printf("*************************************\n");
    printf("Erkang's heuristic\n");

    int ** result = (int**) malloc(NB_MACHINES * sizeof(int*));
    if (result == NULL)
    {
        exit(1);
    }
    initializeResultTable(result, nbJobs);


    // 1. find the critical machine
    /*
     * Critical machine: the machine that has the longest processing time
     *
     */
    printf("*************************************\n");
    printf("Step 1. Find the critical machine\n");
    double processingTimes[NB_MACHINES];
    for (int i = 0; i < NB_MACHINES; i++)
    {
        for (int j = 0; j < nbJobs; j++)
        {
            processingTimes[i] += jobs[j]->pt[i];
        }
    }
    int rankedMachines[NB_MACHINES];
    sortArray(processingTimes,NB_MACHINES,rankedMachines);
    int indexCriticalMachine = rankedMachines[0];
    printf("The critical machine is %d\n", indexCriticalMachine);

    // 2. calculate the critical sequence
    /*
     * Critical sequence: the smith order on the critical machine
     * Smith order: sorting jobs by (processing time / weight)
     */
    printf("*************************************\n");
    printf("Step 2: calculate the critical sequence\n");
    double smithValues[nbJobs];
    for(int i = 0; i < nbJobs; i++)
    {
        smithValues[i]=(double)jobs[i]->pt[indexCriticalMachine] / jobs[i]->w;
    }
    int sequenceSmith[nbJobs];
    sortArray(smithValues, nbJobs, sequenceSmith);
    printf("The Smith sequence calculated: \n");
    for (int i = nbJobs - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            printf("%d \n", sequenceSmith[i]);
        }
        else
        {
            printf("%d -> ", sequenceSmith[i]);
        }
    }

    // 3. apply the critical sequence to all the machines
    /*
     * Key point of heuristic
     */
    printf("*************************************\n");
    printf("Step 3: apply the critical sequence to all the machines\n");
    for (int j = 0; j < NB_MACHINES; j++)
    {
        for (int i = 0; i < nbJobs; i++)
        {
            result[j][i] = sequenceSmith[nbJobs - 1 - i];
        }
    }
    printResultTable(result, nbJobs);


    // 4. scheduling
    /*
     * Key function: scheduling. Scheduling order must be defined before calling scheduling.
     *
     * This step is for calculating the start time for each job on each machine according to
     * the result table.
     *
     */
    printf("*************************************\n");
    printf("Step 4: Scheduling\n");

    //scheduleOnAllMachines(result, jobs, nbJobs, indexCriticalMachine);
    int order[NB_MACHINES] = {0,1,2,3};
    printf("Scheduling order is: %d -> %d -> %d -> %d\n\n",
                          order[0], order[1], order[2], order[3]);
    schedule(result, order, jobs, nbJobs);

    // 5. print result
    double wct = weightedCompleteTime(jobs, nbJobs);
    printf("Weighted completion time: %f \n", wct);
    printf("\nEnd\n\n");
    //save the result for visualisation
    saveJobs(jobs, nbJobs, "jobs.txt");

    // 6. clean memory usage
    for (int i = 0; i < NB_MACHINES; i++)
    {
        free(result[i]);
    }
    free(result);
}




void scheduleOnAllMachines(int** result, Job** jobs, int nbJobs, int indexCriticalMachine)
{
    /*
     * Function not used
     */
    // 1. Schedule on the critical machine (calculate the start time of job)
    printf("************** Start of scheduling ****************\n");
    printf("1. Start of scheduling on the critical machine\n\n");
    int* sequence = result[indexCriticalMachine];
    int cumulatedTime = 0;
    for (int i = 0; i < nbJobs; i++)
    {
        Job* jobConcerne = jobs[sequence[i]];
        jobConcerne->start[indexCriticalMachine] = cumulatedTime;
        cumulatedTime = jobConcerne->start[indexCriticalMachine] + jobConcerne->pt[indexCriticalMachine];
    }

    printf("End of scheduling on critical machine. \n\n");

    // 2. Schedule on other machines
    printf("2. Start of scheduling on other machines\n\n");

    int machineOrder[NB_MACHINES-1];
    int j = 0;
    for (int i = 0; i < NB_MACHINES; i++)
    {
        if (i == indexCriticalMachine)
        {
            continue;
        }
        machineOrder[j++] = i;
    }

    for (int i = 0; i < NB_MACHINES - 1; i++)
    {
        scheduleOnOneMachine(result, jobs, nbJobs, machineOrder[i]);
    }

    for (int i = 0; i < nbJobs; i++)
    {
        printJob(jobs[i]);
    }


    printf("************** End of scheduling *****************\n");
}

void scheduleOnOneMachine(int** result, Job** jobs, int nbJobs, int indexMachine)
{
    /*
     * Function not used
     */
    /*
     * Start time of job i = max {cumulatedTime, max{the end times of job i on other machines}}
     */
    printf("Start of scheduling on machine %d\n\n", indexMachine);
    int cumulatedTime = 0;
    int* sequence = result[indexMachine];
    for (int i = 0; i < nbJobs; i++)
    {
        Job* jobConcerne = jobs[sequence[i]];
        jobConcerne->start[indexMachine] = MACRO_MAX(cumulatedTime, getLatestEndTime(jobConcerne));
        cumulatedTime = jobConcerne->start[indexMachine] + jobConcerne->pt[indexMachine];
    }

    printf("End of scheduling on machine %d\n\n", indexMachine);
}



