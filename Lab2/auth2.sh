#!/bin/bash

while true
do
	echo "Nhap ten: "
	read ten
	echo "Nhap MSSV: "
	read mssv

	if [ $ten = "Thang" ] && [ $mssv = "23521421" ] 
	then
		echo "Yello"
		break
	else
		echo "access denied"
		echo "Hay nhap lai"
	fi
done
exit 0

