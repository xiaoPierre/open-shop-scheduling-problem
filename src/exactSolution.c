//
// Created by zhang on 16/01/17.
//

#include "exactSolution.h"
void exactSolution(Job** jobs, int nbJobs)
{
    /* Note: This is not the real exact solution.
     * The exact solution is composed of two tables: one table with dimension [NB_MACHINES][NB_JOBS] representing the job sequence in each machine,
     * another table with [NB_JOBS][NB_MACHINES] representing the order of machine for each job 
     * (as we are in open-shop case, this order is not unique)
     * Finally, the total number of solutions for open-shop is ((4!)^n) * ((n!)^4) with 4 machines and n jobs
     * n = 5: 10e14  n=10: 10e38  n=20: 10e97 ??? try with n=3 at first time.. (5e6 solutions)
     */

    /*
     * Enumeration algorithm has a complexity of (4!) * O((n!)^4)
     * It can only be calculated when nbJobs is really small (5? 6?)
     * I don't know how to create and store integer array permutation in C! Let Corentin do this!
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
