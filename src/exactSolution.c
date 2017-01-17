//
// Created by zhang on 16/01/17.
//

#include "exactSolution.h"
void exactSolution(Job** jobs, int nbJobs)
{
    /*
     * Enumeration algorithm has a complexity of O((n!)^4)
     * It can only be calculated when nbJobs is really small (5? 6?)
     * I don't know how to create and store integer array permutation in C!
     * I can use python to generate the permutation easily though..
     */
    if (nbJobs > 5)
    {
        printf("I cannot calculate for the exact solution. \n");
        exit(1);
    }
    printf("*************************************\n");
    printf("Exact solution: \n");
    // result for the final exact solution
    int ** result = (int**) malloc(NB_MACHINES * sizeof(int*));
    if (result == NULL)
    {
        exit(1);
    }
    initializeResultTable(result, nbJobs);

    permute(4);

    //enumeration of all possible sequences and all possible scheduling order


}
void permute(int nbJobs) {
    printf("permute function\n");

}

/* Function to swap values at two pointers */
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}