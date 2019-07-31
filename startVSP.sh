#!/bin/bash

if [ -z $1 ]
then
    socat -d -d pty,raw,echo=0 pty,raw,echo=0
else
    socat -d -d -lf $1 pty,raw,echo=0 pty,raw,echo=0
fi

