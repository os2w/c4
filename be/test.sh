#!/bin/bash
# might take a while....

make clean
make noouttest

res="test_results.txt"

for f in "tests/"*; do
	rm c4cache
	tmp=`bin/c4test < $f`
	echo "$f: " >> $res
	echo "$tmp" >> $res
	echo "" >> $res
done

echo "testing done, see $res"
