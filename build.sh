#!/bin/bash

i=1
while [ $i -ne 0 ]
do
    go build &> /dev/null
    i=$?
#    echo $i
done
./TCP
