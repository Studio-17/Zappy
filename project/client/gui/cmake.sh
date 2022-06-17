#!/bin/bash

pwd
cd client/gui/
mkdir -p build/
cd build/
cmake ..
cmake --build .