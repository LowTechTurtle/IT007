#!/bin/bash

if [ -z "$1" ]; then
	echo "Nhap id sinh vien bang command line argument"
	exit 1
fi

student_id=$1
IFS=';'

while read -r id name score; do
	if [ $id = "StudentID" ]; then
		continue
	fi

	if [ $id = $student_id ]; then

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
		echo "Tên: $name"
		echo "Điểm gốc: $score"
		echo "Điểm chữ: $grade"
		break
	fi

done < gradebook.csv
