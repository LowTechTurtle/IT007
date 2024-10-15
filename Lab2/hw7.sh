#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Command line argument gom string va duong dan"
    exit 1
fi

search_string=$1
directory=$2

if [ ! -d "$directory" ]; then
    echo "Khong ton tai $directory"
    exit 1
fi

for file in "$directory"/*; do
	if [ -f "$file" ]; then
		found=$(grep "$search_string" "$file")
		if [ -n "$found" ]; then
			echo $file
			echo $found
			echo "------------------------------"
		fi
	fi
done
