//
// Created by zhang on 14/01/17.
//

#include "tool.h"

void sortArray(double* arrayOfDoubles,int sizeArray,int* array){
    /*
     * algo de tri recursif par fusion
     *
     *
     */
    // Si le tableau n'a qu'un élément, il est déjà trié.
    if(sizeArray<=1){
        array[0]=0;
        return;
    }
    // Sinon, on sépare le tableau en deux parties à peu près égales.
    int half = (int)floor(sizeArray/2);
    int halfbis = sizeArray-half;
    // On trie récursivement les deux parties avec l'algorithme du tri fusion.
    int arrayA[half];
    int arrayB[halfbis];
    sortArray(arrayOfDoubles,half,arrayA);
    sortArray(&arrayOfDoubles[half],halfbis,arrayB);
    // On fusionne les deux tableaux triés en un tableau trié.
    int j = 0; // pour le tableau A
    int k = 0; // pour le tableau B
    int i = 0; // indique où on en est
    for(i;i < sizeArray ; ++i){
        if( j < half && k < halfbis){
            if(arrayOfDoubles[arrayA[j]]>=arrayOfDoubles[half+arrayB[k]]){
                // le plus grand element est dans le tableau A
                array[i]=arrayA[j];
                j++;
            }else{
                // le plus grand element est dans le tableau B
                array[i]=half+arrayB[k];
                k++;
            }
        }else{
            // un tableau a été déjà entièrement restitué dans la fusion
            break;
        }
    }
    if(j==half && k < halfbis){
        // Il ne reste que des éléments de B à insérer dans smith
        for(int t=i;t<sizeArray;t++){
            array[t]=half+arrayB[k];
            k++;
        }
    }
    if(j<half && k == halfbis){
        // Il ne reste que des éléments de A à insérer dans smith
        for(int t=i;t<sizeArray;t++){
            array[t]=arrayA[j];
            j++;
        }
    }
}

void getProcessingTime(Job **jobs,int nbJobs, double* processingTimes,int* jobsParMachines){

    /*
     * Calcule le temps de traitement cumulé des tâches de machines
     */
    for(int i=0;i<NB_MACHINES;i++){
        processingTimes[i] = 0.;
        jobsParMachines[i] = 0;
    }
    for(int i=0;i<nbJobs;i++){
        for(int j=0;j<NB_MACHINES;j++){
            processingTimes[j] += jobs[i]->pt[j];
            if(jobs[i]->pt[j] >0){jobsParMachines[j]++;}
        }
    }
}

void printResultTable(int** result, int nbJobs)
{
    int i, j;
    for (i = 0; i < NB_MACHINES; i++)
    {
        printf("Sequence for machine %d : [ ", i);
        for (j = 0; j < nbJobs; j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("]\n");
    }
}

void saveJobs(Job** jobs, int nbJobs, char* fileName)
{
    FILE *pFile = fopen(fileName, "w");
    for (int i = 0; i < nbJobs; i++)
    {
        char str1[60];
        toStringJob(jobs[i], str1);
        fputs(str1, pFile);
    }
    fclose(pFile);
}

void schedule(int** result, int* order, Job** jobs, int nbJobs)
{
    /*
     * pour mettre job i sur machine j, on a deux cas suivants:
     *
     * 1. on peut trouver un créneau avant / entre deux tâches i
     * (interval tree?)
     *
     * 2. on le met à la dernière tâche de fin du job i
     *
     *
     * tout ça revient à implémenter un interval tree, ajouter une par une l'intervalle
     *
     */

    Node** rootsForJobs = malloc(nbJobs * sizeof(Node*));
    for (int i = 0; i < nbJobs; i++)
    {
        rootsForJobs[i] = NULL;
    }

    for (int i = 0; i < NB_MACHINES; i++)
    {
        int indexMachine = order[i];
        //printf("-------------------------------------\n");
        //printf("Scheduling on machine %d\n", indexMachine);
        int* sequence = result[indexMachine];
        int cumulatedTime = 0;
        for (int j = 0; j < nbJobs; j++)
        {
            int idOfJob = sequence[j];
            Job* jobConcerne = jobs[idOfJob];

            //decide the start time of job
            jobConcerne->start[indexMachine] = decideStartTime(jobConcerne, cumulatedTime, rootsForJobs[idOfJob], indexMachine);
            //printf("the start time decided for job %d is %d\n", jobConcerne->id - 1, jobConcerne->start[indexMachine]);
            //insert into his interval tree
            Interval temp = {jobConcerne->start[indexMachine], jobConcerne->start[indexMachine] + jobConcerne->pt[indexMachine]};
            rootsForJobs[idOfJob] = insert(rootsForJobs[idOfJob], temp);

            //update cumulated time
            cumulatedTime = jobConcerne->start[indexMachine] + jobConcerne->pt[indexMachine];
            //printf("now the cumulated time is %d\n", cumulatedTime);
        }
    }
    //printf("-------------------------------------\n");

    /*
    for (int i = 0; i < nbJobs; i++)
    {
        printJob(jobs[i]);
    }
    */

    for (int i = 0; i < nbJobs; i++)
    {
        free(rootsForJobs[i]);
    }
    free(rootsForJobs);
}

int decideStartTime(Job* job, int accumulatedTime, Node* intervalTree, int indexMachine)
{
    /*
     * Function for deciding the earliest possible start time for job on machine(indexMachine)
     * Function totally not-optimized
     */
    //inOrder(intervalTree);

    /*
     * We have [NB_MACHINES + 1] possibilities for the start time:
     *   1. start from the end time of job on machine i (i = 0, 1, ..., NB_MACHINE - 1)
     *   2. start from the current accumulated time on current scheduling machine
     *
     */
    Interval candidates[NB_MACHINES + 1];
    int processTime = job->pt[indexMachine];
    candidates[NB_MACHINES] = (Interval){accumulatedTime, accumulatedTime + processTime};
    for (int i = 0; i < NB_MACHINES; i++)
    {
        if (job->start[i] < 0)        // not yet scheduled
        {
            candidates[i] = (Interval){accumulatedTime, accumulatedTime + processTime};
        }
        else    //already scheduled
        {
            candidates[i] = (Interval) {job->start[i] + job->pt[i], job->start[i] + job->pt[i] + processTime};
        }
    }
    // give a (big) initial value for start time
    int latestEndTime = getLatestEndTime(job);

    int minimumStartTime = MACRO_MAX(accumulatedTime, latestEndTime);

    // examine all the possibilities, find the minimal start time
    for (int i = 0; i < NB_MACHINES + 1; i++)
    {
        if (overlap(candidates[i], intervalTree) == 0)
        {
            if (candidates[i].low < minimumStartTime && candidates[i].low >= accumulatedTime)
            {
                minimumStartTime = candidates[i].low;
                //printf("Find minimal start time is %d\n", minimumStartTime);
            }
        }
        else
        {
            //printf("overlap!\n");
        }
    }
    // the minimal start time we found should not be smaller than the accumulated time
    //printf("The lastest end time is %d\n", latestEndTime);

    return minimumStartTime;
}


double weightedCompleteTime(Job** jobs, int nbJobs)
{
    double count = 0;
    for (int i = 0; i < nbJobs; i++)
    {
        Job* jobConcerned = jobs[i];
        int endTime = getLatestEndTime(jobConcerned);
        count += jobConcerned->w * endTime;
    }
    return count;
}
