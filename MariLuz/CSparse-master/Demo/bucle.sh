#!/bin/bash
for i in {1..20}
do
   echo "Iter $i: "
   let j=i+1
   ./cs_demo4 mp11.txt "${i}.txt" | sort -n -o "${j}.txt" 
done
