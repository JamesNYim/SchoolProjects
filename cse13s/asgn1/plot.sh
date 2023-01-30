#!/bin/bash

#Collatz Sequence Lengths#
rm -f /tmp/length.dat
for i in {1..10000}; do
	echo -n $i \  >> /tmp/length.dat #the / is for the spacing for coords.. why? idk
	./collatz -n $i | wc -l >> /tmp/length.dat 
done

gnuplot <<END
	 set terminal pdf
	 set output "collatzLengths.pdf"
	 set title "Sequence Lengths"
	 set xlabel "n"
	 set ylabel "lengths"
	 plot "/tmp/length.dat" with dots title ""
END

#Collatz Maximum Sequence Values
rm -f /tmp/maxSequence.dat
for i in {1..10000}; do
	echo -n $i \  >> /tmp/maxSequence.dat
	./collatz -n $i | sort -n | tail -n 1 >> /tmp/maxSequence.dat
done
gnuplot <<END
	 set terminal pdf
	 set output "collatzMaxSeq.pdf"
	 set title "Max Sequence"
	 set xlabel "n"
	 set ylabel "values"
 	 set yrange [0:100000]
	 plot "/tmp/maxSequence.dat" with dots title ""
END

##Collatz Histogram
rm -f /tmp/histogram.dat

#Getting Sequence Lengths
rm -f /tmp/length.dat
for i in {1..10000}; do
	./collatz -n $i | wc -l >> /tmp/length.dat
	cat /tmp/length.dat | sort -n > /tmp/lengthsInOrder.dat
done
	
cat /tmp/lengthsInOrder.dat | uniq -c >> /tmp/histogram.dat


gnuplot <<END
	 set terminal pdf
	 set output "collatzHistogram.pdf"
	 set title "Collatz Histogram"
	 set xlabel "length"
	 set ylabel "frequency"
	 plot "/tmp/histogram.dat" using 2:1 with impulses title ""
END
