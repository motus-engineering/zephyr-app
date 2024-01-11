#!/bin/bash

sudo mkdir ${DEV_TOOLS_ROOT}

#Renode Tools
echo "Installing renode in tools"
sudo rm -rf ${DEV_TOOLS_ROOT}/renode
sudo wget https://builds.renode.io/renode-latest.pkg.tar.xz -P ${DEV_TOOLS_ROOT}/renode 
sudo tar xf ${DEV_TOOLS_ROOT}/renode/renode-latest.pkg.tar.xz -C ${DEV_TOOLS_ROOT}/renode --strip-components=1

echo "Getting gdb-multiarch for debugging with renode"
sudo apt-get update -y 
sudo apt-get install -y gdb-multiarch

echo "Getting renode visualizer for parsing logs"
pip install -r ${DEV_TOOLS_ROOT}/renode/renode/tools/metrics_analyzer/metrics_visualizer/requirements.txt
pip install PyQt6

echo "Getting requirements for west emulate command"
pip install 'pyrenode3[all] @ git+https://github.com/antmicro/pyrenode3.git'
pip install git+https://github.com/antmicro/dts2repl.git
pip3 install devicetree