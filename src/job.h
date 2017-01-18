//
// Created by zhang on 14/01/17.
//

#ifndef OPENSHOP_JOB_H
#define OPENSHOP_JOB_H
#define NB_MACHINES 4

typedef struct Job Job;

struct Job
{
    int id;

    /* donnees fournies */
    int pt[NB_MACHINES];/* temps de traitement sur les machines*/
    int w; /* poids du job */

    /* a calculer */
    int start[NB_MACHINES];/* date de début sur les machines*/

    /* Next job (liste chainée) */
    Job* next;
};

void printJob(Job* job);
//save the string representation of job into file for visualisation
char* toStringJob(Job* job, char* str);

int getLatestEndTime(Job* job);



#endif //OPENSHOP_JOB_H
