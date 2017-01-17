//
// Created by zhang on 14/01/17.
//
//
// Created by zhang on 14/01/17.
//
#include "init.h"
int initJobs(char* fileName, Job** jobs)
{
    /********** INITIALISATION *******/

    FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = "";
    int nbJobs=0;

    fichier = fopen(fileName, "r");

    if (fichier != NULL){
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            Job* job = malloc((int)sizeof(Job));
            *(jobs+nbJobs) = job;
            nbJobs++;
            sscanf(chaine, "%d %d %d %d %d", &((*job).w),&((*job).pt[0]),&((*job).pt[1]),&((*job).pt[2]),&((*job).pt[3]));
            (*job).id = nbJobs;
            for (int i = 0; i < NB_MACHINES; i++)
            {
                (*job).start[i] = -1;  //-1 : not yet scheduled
            }

        }
        fclose(fichier);
    }

    printf("Il y a %d jobs. \n",nbJobs);
    return nbJobs;
}

void initializeResultTable(int** result, int nbJobs)
{
    /*
     * result table: (NB_MACHINES * NBJOBS) with scheduling sequence on each machine
     * Initialize the result scheduling tables with 0
     */
    int i, j;
    for (i = 0; i < NB_MACHINES; i++)
    {
        int* resultOneMachine = (int*) malloc(nbJobs * sizeof(int));
        for (j = 0; j < nbJobs; j++)
        {
            resultOneMachine[j] = 0;
        }
        result[i] = resultOneMachine;
    }
}
