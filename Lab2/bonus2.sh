#!/bin/bash

echo "Nhap vao ten: "
read ten

if [ ! -d $ten ]; then
mkdir $ten 
fi
cd $ten

while read subject; do
if [ ! -d $subject ]; then
mkdir $subject
fi
done < ../subject.txt