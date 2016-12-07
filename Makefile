SHELL := /bin/bash

trm: trm.cpp
	g++ --std=c++11 $^ -o $@

self: trm
	cat self.trm | ./trm 10000 500 > self.out
	diff self.out <(cat self.trm | sed 's/ //g')
