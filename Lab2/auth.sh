#!/bin/bash
echo "Nhap ten: "
read ten
echo "Nhap MSSV: "
read mssv

if [ $ten = "Thang" ] && [ $mssv = "23521421" ] 
then
	echo "Yello"
else
	echo "access denied"
fi

exit 0

