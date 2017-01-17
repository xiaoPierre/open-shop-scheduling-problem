//
// Created by zhang on 14/01/17.
//

#ifndef ORDO_HEURISTIQUEERKANG_H
#define ORDO_HEURISTIQUEERKANG_H

#include "tool.h"
#include "init.h"
#include "intervalTree.h"


void heuristiqueErkang(Job** jobs, int nbJobs);
void scheduleOnAllMachines(int** result, Job** jobs, int nbJobs, int indexCriticalMachine);
void scheduleOnOneMachine(int** result, Job** jobs, int nbJobs, int indexMachine);



#endif //ORDO_HEURISTIQUEERKANG_H
