#!/bin/bash

#cd ../../../
docker rmi -f desperos_sprintf
docker build . -t desperos_sprintf -f ./Dockerfile_sprintf
docker run --rm desperos_sprintf
