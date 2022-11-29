#!/bin/bash

#cd ../../../
docker rmi -f desperos/valgrind/grep
docker build . -t desperos/valgrind/grep -f materials/build/Valgrind/Dockerfile
docker run --rm desperos/valgrind/grep
