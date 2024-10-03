#!/bin/bash

make -C build

if [ $? -eq 0 ]; then
    ./build/Userland/CLI/CLI $1
else
    echo "Build failed. Exiting."
fi
