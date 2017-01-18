#/bin/bash

if [ -d "build"]; then
rmdir "build"
mkdir "build"
else
mkdir "build"
fi

cd build
cmake ..
make

./heuristique ../data.txt

python3 ../vis.py heuristique.txt
python3 ../vis.py genetic.txt
