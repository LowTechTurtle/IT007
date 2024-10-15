#!/bin/bash

for ((i=0; i<5; i++))
do
	echo "Nhap ten: "
	read ten
	echo "Nhap MSSV: "
	read mssv

	if [ $ten = "Thang" ] && [ $mssv = "23521421" ] 
	then
		echo "Yello"
		exit 0
	else
		echo "access denied"
		if [ $i -lt 4 ]
		then
			echo "Hay nhap lai"
		else
			echo "Ban da het lan thu"
		fi
	fi
done
exit 0

