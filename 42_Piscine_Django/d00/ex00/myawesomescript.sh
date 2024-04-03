#!/bin/sh

if [ "$#" -eq 1 ] && (echo "$1" | grep -qE '^https?://bit\.ly|bit\.ly'); then
    curl -sI "$1" | grep -i location | cut -d ' ' -f2
fi