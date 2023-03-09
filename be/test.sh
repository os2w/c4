#!/bin/bash
# might take a while....

make clean
make noouttest

res="test_results.txt"
tests=(endeasy mideasy midmedium begeasy begmedium beghard)

rm $res

cpu=`lscpu | grep "Model name:" | sed -r 's/Model name:\s{1,}//g'`
mhz=`lscpu | grep "CPU MHz:" | sed -r 's/CPU MHz:\s{1,}//g'`
mem=`awk '/MemFree/ { printf "%.3f\n", $2/1024/1024 }' /proc/meminfo`

echo "cpu: $cpu @ $mhz MHz" >> $res
echo -e "mem: $mem GB\n" >> $res

for f in ${tests[@]}; do
	rm c4cache
	tmp=`bin/c4test < tests/$f`
	echo "$f: " >> $res
	echo -e "$tmp\n" >> $res
done

echo "testing done, see $res"
