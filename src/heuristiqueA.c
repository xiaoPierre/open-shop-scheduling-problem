#include "init.h"
#include "tool.h"
#include "heuristiqueErkang.h"
#include "exactSolution.h"
#include "intervalTree.h"
#include "genetic.h"

#define MAX_JOB 10000

int main(int argc, char *argv[]){


    Job **jobs = malloc(MAX_JOB * sizeof(Job*));
    int nbJobs = initJobs("data.txt", jobs);
    genetic(jobs, nbJobs);
    reinitializeJobs(jobs, nbJobs);
    heuristiqueErkang(jobs, nbJobs);
    //testTree();

    // libérer les mémoires  (jobs et smithValues)



    /*
     * partie de Corentin
     *
     *
     *
     *
     *
     *    //********** SMITH **********
    double* smithValues[NB_MACHINES];
    for(int j=0;j<NB_MACHINES;j++){
        smithValues[j]= malloc(nbJobs);
    }
    for(int i=0;i<nbJobs;i++){
        for(int j=0;j<NB_MACHINES;j++){
            smithValues[j][i]=(double)jobs[i]->pt[j]/jobs[i]->w;
        }
    }
    int *sortedJobs[NB_MACHINES];
    // Machine 1
    int smith1[nbJobs];
    sortedJobs[0]=smith1;
    sortArray(smithValues[0],nbJobs,smith1);
    // Machine 2
    int smith2[nbJobs];
    sortedJobs[1]=smith2;
    sortArray(smithValues[1],nbJobs,smith2);
    // Machine 3
    int smith3[nbJobs];
    sortedJobs[2]=smith2;
    sortArray(smithValues[2],nbJobs,smith3);
    // Machine 4
    int smith4[nbJobs];
    sortedJobs[3]=smith3;
    sortArray(smithValues[3],nbJobs,smith4);


    //******* CLASSEMENT MACHINE ******
    double processingTimes[NB_MACHINES];
    int jobsParMachines[NB_MACHINES];
    getProcessingTime(jobs,nbJobs,processingTimes,jobsParMachines);
    // tri des machines par temps de traitement cumulé
    int rankedMachines[NB_MACHINES];
    sortArray(processingTimes,NB_MACHINES,rankedMachines);


    //********** ORDONNANCEMENT ******

    int* sequences[NB_MACHINES];

    // Ordonnancement des tâches sur la machine critique
    int sequence[jobsParMachines[rankedMachines[0]]];
    sequences[rankedMachines[0]]=sequence;
    int processed=0;
    int j=0; // verifie qu'on depasse pas la taille du tab (un try catch serait mieux..)
    for(int i=0;i<nbJobs;i++){
        if (jobs[sortedJobs[rankedMachines[0]][i]]->pt[rankedMachines[0]] > 0 ){
            if(j==jobsParMachines[rankedMachines[0]]){
                printf("ERREUR: Depassement du tableau de sequencement \n");
                exit(0);
            }
            else{
                sequences[rankedMachines[0]][j] = sortedJobs[rankedMachines[0]][i];
                jobs[sortedJobs[rankedMachines[0]][i]]->start[rankedMachines[0]] = processed;
                processed += jobs[sortedJobs[rankedMachines[0]][i]]->pt[rankedMachines[0]];
                j++;
            }
        }
    }

    // Ordonnancement des tâches sur les machines suivantes
    for(int k=1;k<NB_MACHINES;k++){
        int sequence[jobsParMachines[rankedMachines[k]]];
        sequences[rankedMachines[k]]=sequence;
        int processed=0;
        int j=0; // verifie qu'on depasse pas la taille du tab
        for(int i=0;i<nbJobs;i++){
            // TODO!!!!
        }
    }


    // EXEMPLE D'UTILISATION DE LA STRUCTURE JOB ET DES CLASSEMENTS DE SMITH

    // Afficher la valeur p/w pour le 4e job de la machine 2 selon ordre de Smith:
    printf("Machine 2, 4e valeur de p2/w selon Smith: p2/w =  %f \n", smithValues[1][4]);

    // affiche la machine avec le plus gros temps de traitement cumulé
    printf("Machine critique est la %d, processing time cumulé vaut %d. \n",
           rankedMachines[0]+1,(int)processingTimes[rankedMachines[0]]);

    // Afficher la date de depart sur M1 du job classé 3e selon Smith sur M3:
    printf("Date de depart sur Machine critique du job ordonnancé en 7e: st = %d \n",
           jobs[sequences[rankedMachines[0]][7]]->start[rankedMachines[0]]);

    // Affiche la sequence de la machine critique
    printf("Sequence machine critique: \n");
    for(int i=0;i<jobsParMachines[rankedMachines[0]];i++){
        printf("%d -> ", sequences[rankedMachines[0]][i]+1);
    }
    printf("END \n");
     *
     * fin de partie de Corentin
     */


    return 0;
}
