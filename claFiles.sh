#!/bin/bash

if [ "$1" -a "$2" -a ! "$3" ]; then
    cat "$1" > "$2"
    cat "$2"
    exit 0
elif [ "$1" -a "$2" -a "$3" == "--append" ]; then
    cat "$1" >> "$2"
    echo In file "$2" after append: 
    less -N "$2"
    exit 0
else 
    echo "insert first file: "
    read firstFile
    touch "$firstFile" && echo `date` > "$firstFile"
    echo "input second file: "
    read secodFile
    echo "append: yes/no"
    read append
    if [ "$append" == "yes" ]; then
        cat "$firstFile" >> "$secodFile"
        echo In file "$secodFile" after append: 
        cat "$secodFile"
    else 
        cat "$firstFile" > "$secodFile"
        echo In file "$secodFile": `cat "$secodFile"`
    fi
fi    