#!/bin/bash

docker run -d -it --name pico-sdk --mount type=bind,source=${PWD}/PocketWX,target=/home/dev lukstep/raspberry-pi-pico-sdk:latest

mkdir -p ./PocketWX/build

docker exec -it pico-sdk /bin/sh -c "cd /home/dev/build && cmake .. && make -j4 && exit"
