//
// Created by zhang on 14/01/17.
//

#ifndef OPENSHOP_TOOL_H
#define OPENSHOP_TOOL_H

#include "job.h"
#include "intervalTree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//problem of macro!
#define MACRO_MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

void sortArray(double* arrayOfDoubles,int sizeArray,int* array);

void getProcessingTime(Job **jobs,int nbJobs, double* processingTimes,int* jobsParMachines);
void printResultTable(int** result, int nbJobs);
void saveJobs(Job** jobs, int nbJobs, char* fileName);
void schedule(int** result, int* order, Job** jobs, int nbJobs);
int decideStartTime(Job* job, int accumulatedTime, Node* intervalTree, int indexMachine);
double weightedCompleteTime(Job** jobs, int nbJobs);


#endif //OPENSHOP_TOOL_H
