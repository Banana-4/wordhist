#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename="$1"

if [ ! -f "$filename" ]; then
    echo "Error: '$filename' does not exist or is not a regular file."
    exit 1
fi

count=$(grep -oE "[[:alpha:]][[:alnum:]']*" "$filename" | wc -l)
cols=$(tput cols)
if [ "$count" -gt "$cols" ]; then
	./wordhist h < "$filename" | less
else
	./wordhist < "$filename"
fi
