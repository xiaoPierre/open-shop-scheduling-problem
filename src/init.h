//
// Created by zhang on 14/01/17.
//

#ifndef OPENSHOP_INIT_H
#define OPENSHOP_INIT_H
#include "job.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_JOB 10000
#define TAILLE_MAX 1000 // Tableau de taille 1000
int initJobs(char* fileName, Job** jobs);

void initializeResultTable(int** result, int nbJobs);


#endif //OPENSHOP_INIT_H
