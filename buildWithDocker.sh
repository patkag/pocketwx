#!/bin/bash

mkdir -p ./PocketWX/build

docker run -d -it --rm --name pico-sdk --mount type=bind,source=${PWD}/PocketWX,target=/home/dev lukstep/raspberry-pi-pico-sdk:latest /bin/sh -c "cd /home/dev/build && cmake .. && make -j4 && exit"