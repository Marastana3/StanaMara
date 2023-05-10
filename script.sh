#!/bin/bash

# Check if argument is a regular file with .c extension
if [[ -f "$1" && "$1" == *.c ]]; then
    # Compile file and print number of errors and warnings
    errors=$(gcc -o /dev/null -Wall -Werror "$1" 2>&1 | grep error | wc -l)
    warnings=$(gcc -o /dev/null -Wall -Werror "$1" 2>&1 | grep warning | wc -l)
    echo "Errors: $errors"
    echo "Warnings: $warnings"

# Check if argument is a regular file but doesn't have .c extension
elif [[ -f "$1" ]]; then
    # Print number of lines
    lines=$(wc -l < "$1")
    echo "Number of lines: $lines"

# Check if argument is a directory
elif [[ -d "$1" ]]; then
    # Create file with .txt extension and specific name
    filename="${1##*/}_file.txt"
    touch "$filename"
    echo "Created file $filename"

# Check if argument is a symbolic link
elif [[ -L "$1" ]]; then
    # Change permissions of symbolic link
    chmod u=rwx,g=rw,o= "$1"
    echo "Changed permissions of symbolic link $1"

# If argument is none of the above, print error message
else
    echo "Invalid argument"
fi