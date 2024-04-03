#!/bin/bash

touch /tmp/something

while true;
do
    ln -fs /tmp/something /tmp/fake_ln;
    ln -fs ~/token /tmp/fake_ln;
done
