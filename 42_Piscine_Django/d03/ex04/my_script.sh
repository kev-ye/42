#!/bin/bash

if [ "$0" = "$BASH_SOURCE" ]; then
    echo "Error: This script must be sourced to activate the virtual environment."
    echo "Please run: source $0"
    exit 1
fi

python3 -m venv django_venv
source django_venv/bin/activate
pip3 install -r requirement.txt
