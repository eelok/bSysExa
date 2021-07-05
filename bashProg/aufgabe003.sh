#!/bin/bash
start=$1
end=$2
if [ "$start" -ge "$end" ]; then
    echo "the first parameter has to be smaller than the second parameter"
    exit 1
else
    res = 0
    while [ "$start" -le "$end" ];
    do
        res=$(($res + $start))
        ((++start))
    done
    echo $res
fi    
exit 0
