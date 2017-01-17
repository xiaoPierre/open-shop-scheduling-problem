cmake_minimum_required(VERSION 3.5)
project(ordo)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCE_FILES src/*)


add_executable(heuristique ${SOURCE_FILES} src/heuristiqueErkang.h src/heuristiqueErkang.c src/job.c src/intervalTree.c src/intervalTree.h src/exactSolution.h src/exactSolution.c src/genetic.h src/genetic.c)
target_link_libraries(heuristique m)
