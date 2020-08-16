#!/bin/bash
#useful for running when using vim or other commandline text editor
g++ -pthread CLI.cpp errorMessages.cpp spanningSeeds2.cpp threading.cpp -o registerSequences 
sudo mv numberSequences /usr/local/bin/
