#!/bin/bash

if [[ -z $1 ]]; then
  echo "usage: ./run.sh [arg]: prod / dev / clean"
fi

if [[ $1 == "prod" ]]; then
  docker-compose up --build
fi

if [[ $1 == "dev" ]]; then
  docker-compose -f ./docker-compose-dev.yml up --build
fi

if [[ $1 == "clean" ]]; then
  docker container rm $(docker container ls -a -q) 2> /dev/null
  docker image rm $(docker image ls -q) 2> /dev/null
  docker volume rm $(docker volume ls -q) 2> /dev/null
  docker system prune
fi

