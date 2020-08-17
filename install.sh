#!/bin/bash
# run this script as superuser to install the tool. Will install as registerSequences and download source code. Can also be used as an installation guide
cd ~/Downloads
git clone https://github.com/AvrahamKahan123/spanningSeeds/
cd spanningSeeds/newestVersion
g++ -pthread CLI.cpp errorMessages.cpp spanningSeeds2.cpp threading.cpp -o registerSequences 
sudo mv numberSequences /usr/local/bin/
