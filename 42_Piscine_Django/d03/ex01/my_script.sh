#!/bin/bash

echo "pip version:"
pip3 --version

INSTALL_DIR="./local_lib"
LOG_FILE="install.log"

echo "Installing path.py from GitHub..."
pip3 install --upgrade --target="$INSTALL_DIR" --force-reinstall \
    git+https://github.com/jaraco/path.git > "$LOG_FILE" 2>&1

if [ $? -eq 0 ]; then
    echo "Installation successful! Logs saved to $LOG_FILE"
    echo "Running my_program.py..."
    PYTHONPATH="$INSTALL_DIR:$PYTHONPATH" python3 my_program.py
else
    echo "Installation failed. Check $LOG_FILE for details."
    exit 1
fi
