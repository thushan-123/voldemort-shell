#!/bin/bash
set -e  

mkdir -p build
cd build

cmake ..
make

PATH="/usr/bin:/usr/local/bin:$PATH" ./vdshell
