#!/bin/bash
for i in "$@"
do
str="$i"
done
mkdir submit
x=0
while read line;
do
        strr[$x]="$line"
        x=$(($x+1))
done <$str
cd submit
for ((a=0; a<${#strr[*]};a++))
do
mkdir $strr
done
