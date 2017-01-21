//
// Created by zhang on 16/01/17.
//
#include <time.h>
#include "genetic.h"
#include "init.h"
#define MAX_GENERATION 50
#define NB_SPECIES 500
#define MUTATION_TIME 150
#define CROSS_TIME 150
#define NB_RESERVED_INDIVIDU 20


void genetic(Job** jobs, int nbJobs)
{
    srand((unsigned)time(NULL));

    printf("*************************************\n");
    printf("Genetic algorithm: \n");
    int ** species[NB_SPECIES];

    //init first generation
    /*
     * Initiate with random sequence of jobs
     *
     */
    for (int i = 0; i < NB_SPECIES; i++)
    {
        int ** result = (int**) malloc(NB_MACHINES * sizeof(int*));
        if (result == NULL)
        {
            exit(1);
        }
        initializeResultTable(result, nbJobs);
        initFirstGeneration(result, nbJobs);
        //printResultTable(result, nbJobs);
        species[i] = result;
    }


    int nbGeneration = 0;
    double points[NB_SPECIES];
    while (nbGeneration < MAX_GENERATION)
    {
        // 0. Initialisation of species (all jobs become unscheduled)
        reinitializeJobs(jobs, nbJobs);

        printf("The %d generation:\n", nbGeneration);
        // 1. Evaluation step (calculate fitness of each specie)
        for (int i = 0; i < NB_SPECIES; i++)
        {
            points[i] = evaluateSpecie(species[i], jobs, nbJobs);
        }


        // 2. Selection step
        selectOperator(species, points, nbJobs);
        printf("The point of this generation is %f\n", evaluateSpecie(species[0], jobs, nbJobs));

        // 3. Cross step
        crossOperator(species, nbJobs);

        // 4. Mutation step
        mutationOperator(species, nbJobs, nbGeneration);
        nbGeneration++;

    }
    int ** result;
    result = chooseBestSpecie(species, points);
    scheduleBestSpecie(result, jobs, nbJobs);
    saveJobs(jobs, nbJobs, "genetic.txt");



    printf("*************************************\n");

    // 6. clean memory usage
    for (int i = 0; i < NB_SPECIES; i++)
    {
        for (int j = 0; j < NB_MACHINES; j++)
        {
            free(species[i][j]);
        }
        free(species[i]);
    }
}

void initFirstGeneration(int** result, int nbJobs)
{
    for (int i = 0; i < NB_MACHINES; i++)
    {
        result[i] = getRandomSequence(nbJobs);
    }
}

int* getRandomSequence(int nbJobs)
{

    int* sequence = malloc(nbJobs * sizeof(int));
    int* existed = malloc(nbJobs * sizeof(int));
    for (int i = 0; i < nbJobs; i++)
    {
        existed[i] = 0;
        sequence[i] = 0;
    }

    for (int i = 0; i < nbJobs; i++)
    {
        int ran = rand() % nbJobs;
        //printf("random value: %d\n", ran);
        while (existed[ran])
        {
            ran = (ran + 1) % nbJobs;
        }
        sequence[i] = ran;
        existed[ran] = 1;
    }

    free(existed);
    return sequence;
}

double evaluateSpecie(int** result, Job** jobs, int nbJobs)
{
    /*
     * Roughly evaluate each specie by scheduling with 4 different orders and take the best
     * May be improved? Or not so important to evaluate precisely each specie?
     */
    int orderA[NB_MACHINES] = {0, 1, 2, 3};
    int orderB[NB_MACHINES] = {1, 2, 3, 0};
    int orderC[NB_MACHINES] = {2, 3, 1, 0};
    int orderD[NB_MACHINES] = {3, 1, 2, 0};

    double minPoint = 0;
    int idxOrder = 0;
    reinitializeJobs(jobs, nbJobs);
    schedule(result, orderA, jobs, nbJobs);
    minPoint = weightedCompleteTime(jobs, nbJobs);

    reinitializeJobs(jobs, nbJobs);
    schedule(result, orderB, jobs, nbJobs);
    double pointB = weightedCompleteTime(jobs, nbJobs);
    if (pointB < minPoint)
    {
        minPoint = pointB;
        idxOrder = 1;
    }

    reinitializeJobs(jobs, nbJobs);
    schedule(result, orderC, jobs, nbJobs);
    double pointC = weightedCompleteTime(jobs, nbJobs);
    if (pointC < minPoint)
    {
        minPoint = pointC;
        idxOrder = 2;
    }

    reinitializeJobs(jobs, nbJobs);
    schedule(result, orderD, jobs, nbJobs);
    double pointD = weightedCompleteTime(jobs, nbJobs);
    if (pointD < minPoint)
    {
        minPoint = pointD;
        idxOrder = 3;
    }
    //printf("The decided scheduling order is %d\n", idxOrder);
    reinitializeJobs(jobs, nbJobs);
    return minPoint;
}

void selectOperator(int*** species, double* points, int nbJobs)
{
    /*
     * Select the specie with highest score
     * Copy this specie for others
     */
    int idxSpecie = 0;
    double minPoint = points[0];
    for (int i = 0; i < NB_SPECIES; i++)
    {
        if (points[i] < minPoint)
        {
            minPoint = points[i];
            idxSpecie = i;
            //printf("valeur %d\n", idxSpecie);
        }
    }

    printf("The best specie is number %d\n", idxSpecie);
    printResultTable(species[idxSpecie], nbJobs);

    /*
    //update other species
    for (int i = 0; i < NB_SPECIES; i++)
    {
        for (int j = 0; j < NB_MACHINES; j++)
        {
            for (int k = 0; k < nbJobs; k++)
            {

                {
                    species[i][j][k] = species[idxSpecie][j][k];
                }
            }
        }
    }
     */


    double seuil = minPoint * 1;
    int* idxList = malloc(NB_RESERVED_INDIVIDU * sizeof(int));
    int j = 0;
    for (int i = 0; i < NB_SPECIES; i++)
    {
        if (points[i] <= seuil)
        {
            idxList[j++] = i;
        }
        if (j == NB_RESERVED_INDIVIDU)
        {
            break;
        }
    }
    printf("Find %d good individus.\n", j);

    // update other species with top j randomly (max NB_RESERVED_INDIVIDU)
    for (int i = 0; i < NB_SPECIES; i++)
    {
        int idxSpecie = idxList[rand() % j];
        for (int l = 0; l < NB_MACHINES; l++)
        {
            for (int k = 0; k < nbJobs; k++)
            {

                {
                    species[i][l][k] = species[idxSpecie][l][k];
                }
            }
        }
    }
    free(idxList);
}

void crossOperator(int*** species, int nbJobs)
{
    /*
     * Do nothing, because all species are the same
     */

    int i = 0;
    while (i < CROSS_TIME)
    {
        int individu1 = rand() % NB_SPECIES;
        int individu2 = rand() % NB_SPECIES;
        int idxMachine = rand() % NB_MACHINES;
        int idxJob = rand() % nbJobs;

        int individu1Before = species[individu1][idxMachine][idxJob];
        int individu2Before = species[individu2][idxMachine][idxJob];

        species[individu1][idxMachine][idxJob] = individu2Before;
        species[individu2][idxMachine][idxJob] = individu1Before;

        // treat the incompability
        for (int j = 0; j < nbJobs; j++)
        {
            if (species[individu1][idxMachine][j] == individu2Before)
            {
                species[individu1][idxMachine][j] = individu1Before;
                break;
            }
        }
        for (int j = 0; j < nbJobs; j++)
        {
            if (species[individu2][idxMachine][j] == individu1Before)
            {
                species[individu2][idxMachine][j] = individu2Before;
                break;
            }
        }
        i++;
    }

}

void mutationOperator(int*** species, int nbJobs, int nbGeneration)
{
    /*
     * Randomly select a specie
     * Randomly choose a machine
     * Randomly exchange two job id
     * Repeat for MUTATION_TIME times
     */

    for (int i = 0; i < MUTATION_TIME * (MAX_GENERATION - nbGeneration); i++)
    {
        int idxSpecie = rand() % NB_SPECIES;
        int machine = rand() % NB_MACHINES;
        int jobid1 = rand() % nbJobs;
        int jobid2 = rand() % nbJobs;

        int temp;
        temp = species[idxSpecie][machine][jobid1];
        species[idxSpecie][machine][jobid1] = species[idxSpecie][machine][jobid2];
        species[idxSpecie][machine][jobid2] = temp;
    }
}

void reinitializeJobs(Job** jobs, int nbJobs)
{
    for (int i = 0; i < nbJobs; i++)
    {
        for (int j = 0; j < NB_MACHINES; j++)
        {
            jobs[i]->start[j] = -1;
        }
    }
}

int ** chooseBestSpecie(int*** species, double* points)
{
    int minIdx = 0;
    double minPoint = points[0];
    for (int i = 1; i < NB_SPECIES; i++)
    {
        if (points[i] < minPoint)
        {
            minPoint = points[i];
            minIdx = i;
        }
    }
    return species[minIdx];
}

void scheduleBestSpecie(int** result, Job** jobs, int nbJobs)
{
    int orders[24][4] =
            {
                    {0,1,2,3},
                    {0,1,3,2},
                    {0,2,1,3},
                    {0,2,3,1},
                    {0,3,1,2},
                    {0,3,2,1},
                    {1,0,2,3},
                    {1,0,3,2},
                    {1,2,3,0},
                    {1,2,0,3},
                    {1,3,0,2},
                    {1,3,2,0},
                    {2,0,1,3},
                    {2,0,3,1},
                    {2,1,0,3},
                    {2,1,3,0},
                    {2,3,1,0},
                    {2,3,0,1},
                    {3,0,1,2},
                    {3,0,2,1},
                    {3,1,0,2},
                    {3,1,2,0},
                    {3,2,1,0},
                    {3,2,0,1}
            };
    int* bestOrder;
    reinitializeJobs(jobs, nbJobs);
    schedule(result, orders[0], jobs, nbJobs);
    double minPoint = weightedCompleteTime(jobs, nbJobs);
    int minIdx = 0;

    for (int i = 0; i < 24; i++)
    {
        int* order = orders[i];
        reinitializeJobs(jobs, nbJobs);
        schedule(result, order, jobs, nbJobs);
        double point = weightedCompleteTime(jobs, nbJobs);
        if (point < minPoint)
        {
            minPoint = point;
            minIdx = i;
        }
    }
    bestOrder = orders[minIdx];
    reinitializeJobs(jobs, nbJobs);
    schedule(result, bestOrder, jobs, nbJobs);
}

