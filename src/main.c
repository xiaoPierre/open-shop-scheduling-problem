//
// Created by zhang on 17/01/17.
//
#include "heuristiqueErkang.h"
#include "genetic.h"

int main(int argc, char *argv[]){

    char* inputfile = argv[1];
    Job **jobs = malloc(MAX_JOB * sizeof(Job*));
    int nbJobs=initJobs(inputfile, jobs);

    genetic(jobs, nbJobs);
    initJobs(inputfile, jobs);
    heuristiqueErkang(jobs, nbJobs);

    return 0;

}
