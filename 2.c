#!/bin/bash
if [ -n "$1" ]
then
str="$1"
else
echo "error of parameters">/dev/stderr
fi
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
