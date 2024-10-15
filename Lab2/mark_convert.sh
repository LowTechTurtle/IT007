#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Hay nhap diem( 1 so tu command line argument)"
    exit 1
fi

score=$1

if ! [[ "$score" =~ ^[0-9]+$ ]] || [ "$score" -lt 0 ] || [ "$score" -gt 1000 ]; then
    echo "Hay nhap diem trong khoang tu 0 den 1000"
    exit 1
fi

if [ "$score" -ge 900 ] && [ "$score" -le 1000 ]; then
    grade="A+"
elif [ "$score" -ge 800 ] && [ "$score" -lt 900 ]; then
    grade="A"
elif [ "$score" -ge 700 ] && [ "$score" -lt 800 ]; then
    grade="B+"
elif [ "$score" -ge 600 ] && [ "$score" -lt 700 ]; then
    grade="B"
elif [ "$score" -ge 500 ] && [ "$score" -lt 600 ]; then
    grade="C"
else
    grade="D/F"
fi

echo "Score: $score => Grade: $grade"
