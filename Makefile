SHELL := /bin/bash

trm: trm.cpp
	g++ --std=c++11 $^ -o $@

self: trm
	cat self.trm | ./trm 10000 500 > self.out
	diff self.out <(cat self.trm | sed 's/ //g')

write: trm
	(cat write.trm; echo "R1111####") | ./trm 1000 20 > write.out

move21: trm
	(cat move21.trm; echo "R# R1111####") | ./trm 1000 20 > move21.out

diag: trm
	(cat diag.trm; echo "R1111####") | ./trm 1000 20 > diag.out

quine.trm: trm
	(cat diag.trm; echo "R"; cat diag.trm) | ./trm 10000 500 > $@

quine.out: trm
	cat quine.trm | ./trm 10000 500 > $@

# for p = move2,1
qstar.trm: trm
	(cat q1.trm; echo "R"; cat q1.trm) | ./trm 100000 -1 > $@
