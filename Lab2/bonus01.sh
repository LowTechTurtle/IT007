#!/bin/bash

if [ ! -d OS_LAB2_IMG ]
then
	git clone https://github.com/locth/OS_LAB2_IMG.git
else
	echo "Da co directory OS_LAB2_IMG"
fi

cd OS_LAB2_IMG

if [ ! -d PNG ] 
then
	mkdir PNG
	mv *.png ./PNG
	num_of_png=$(($(ls -l PNG | wc -l) - 1))
	echo "Co $num_of_png file png"
fi

if [ ! -d JPG ] 
then
	mkdir JPG
	mv *.jpg ./JPG
	lsl=$(ls -l JPG)
	num_of_jpg=$(($(ls -l JPG | wc -l) - 1))
	echo "Co $num_of_jpg file jpg"
fi

