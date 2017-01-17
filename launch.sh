#/bin/bash

cmake .
make

./heuristique

python vis.py heuristic.txt
python vis.py genetic.txt
