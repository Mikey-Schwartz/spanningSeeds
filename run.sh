#!bin/bash
#useful for running when using vim or other commandline text editor
g++ -pthread spanningSeeds2.cpp threading.cpp -o spanningSeedsExecutable
./spanningSeedsExecutable
