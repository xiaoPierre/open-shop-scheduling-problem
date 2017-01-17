#/bin/bash

cmake .
make

./heuristique

python vis.py jobs.txt
