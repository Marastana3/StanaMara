#!/bin/bash

# Check if argument is a regular file with .c extension
if [[ -f "$1" && "$1" == *.c ]]; then
    # Compile file and print number of errors and warnings
    errors=$(gcc -o /dev/null -Wall -Werror "$1" 2>&1 | grep error | wc -l)
    warnings=$(gcc -o /dev/null -Wall -Werror "$1" 2>&1 | grep warning | wc -l)
    echo "Errors: $errors"
    echo "Warnings: $warnings"
fi 