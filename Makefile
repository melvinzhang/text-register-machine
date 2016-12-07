trm: trm.cpp
	g++ --std=c++11 $^ -o $@

self: trm
	cat self.trm | ./trm 10000 500

