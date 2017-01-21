# open-shop-scheduling-problem

### Overview
4 machine open-shop scheduling problem with objectif of minimize the total weighted completion time solved with two methods: 
  * an heuristic using Smith order 
  * a genetic algorithm
  * TODO: tabu search algorithm


### Dependencies:
  * python3, PyQt
  * cmake
  * gcc

### Explication of the data file:
  * The jobs data is stored in data.txt
  * Each job is composed by 5 integers. The first integer is its weight, the next 4 integers are the processing time of this job on 4 machines respectively.

### Instructions:
  * launch the ./launch.sh file, the heuristic approch and the algorithm approch will apprear one after another with a PyQT-based visualisation.

### Note:
  * For visualisation, the number of jobs cannot be more than 10.
  
  
### Details of algorithms:
#### 1. heuristic using Smith order:
       * find the critical machine (which has the longest processing time)
       * sort all jobs in Smith order in the critical machine (by (processTime / weight) in ascending order)
       * schedule first on the critical machine with Smith order
       * schedule on other machines with Smith order
       
#### 2. Genetic Algorithm:
       * Codage:
          Each solution is represented by a (NB_JOBS * 4) matrix and a (1 * 4) array  
          (NB_JOBS * 4) matrix: job sequence in each of the 4 machines
          (1 * 4) array: the scheduling order of 4 machine
          
       * Fitness function   
          Same as the objective function
          
       * Selection operator
          Select the best known individuals, copy them in the next generation
          
       * Cross operator
          Choose randomly ** two ** indivuduals.
          Choose randomly a position of gene (an index)
          Exchange these two genes
          
       * Mutation operator
          Choose randomly ** one ** indivudual
          Choose randomly two positions of gene (two index)
          Exchange these two genes
          
 ### Benchmark (on makespan)
 http://mistic.heig-vd.ch/taillard/problemes.dir/ordonnancement.dir/ordonnancement.html
