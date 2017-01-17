//
// Created by zhang on 16/01/17.
//

#ifndef ORDO_GENETIC_H
#define ORDO_GENETIC_H

#include "tool.h"

void genetic(Job** jobs, int nbJobs);
void initFirstGeneration(int** result, int nbJobs);
int* getRandomSequence(int nbJobs);
double evaluateSpecie(int** result, Job** jobs, int nbJobs);
void selectOperator(int*** species, double* points, int nbJobs);
void crossOperator(int*** species, int nbJobs);
void mutationOperator(int*** species, int nbJobs, int nbGeneration);
void reinitializeJobs(Job** jobs, int nbJobs);


#endif //ORDO_GENETIC_H
