#/bin/bash

cd build
cmake ..
make

./heuristique ../data.txt

python3 ../vis.py heuristique.txt
python3 ../vis.py genetic.txt
