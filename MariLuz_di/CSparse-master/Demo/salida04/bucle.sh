#!/bin/bash
for i in {1..30}
do
   echo "Iter $i: "
   let j=i+1
   ../cs_demo4 matriz_paso_04.di.txt "${i}.txt" | sort -n -o "${j}.txt" 
done
