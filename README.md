# open-shop-scheduling-problem
4 machine open-shop scheduling problem with objectif of minimize the total weighted completion time solved with two methods: 
  * an heuristic using Smith order 
  * a genetic algorithm method.


Dependencies:
  * python 3
  * cmake
  * gcc

Explication of the data file:
  * The jobs data is stored in data.txt
  * Each job is composed by 5 integers. The first integer is its weight, the next 4 integers are the processing time of this job on 4 machines respectively.



Instructions:
  * launch the ./launch.sh file, the heuristic approch and the algorithm approch will apprear one after another with a PyQT-based visualisation.

Note:
  * For visualisation, the number of jobs cannot be more than 10.
