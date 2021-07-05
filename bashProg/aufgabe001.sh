#!/bin/bash

if [ "$1" -a "$2" -a ! "$3" ]; then
    cat "$1" > "$2"
    cat "$2"
    exit 0
elif [ "$1" -a "$2" -a "$3" == "--append" ]; then
    cat "$1" >> "$2"
    echo In file "$2" after append: 
    less -N "$2"
else 
    echo "insert first file: "
    read firstF
    touch "$firstF" && echo `date` > "$firstF"
    echo "input second file: "
    read secodF
    echo "append: yes/no"
    read append
    if [ "$append" == "yes" ]; then
        cat "$firstF" >> "$secodF"
        echo In file "$secodF" after append: 
        less -N "$secodF"
    else 
        cat "$firstF" > "$secodF"
        echo In file "$secodF": `cat "$secodF"`
    fi
fi    