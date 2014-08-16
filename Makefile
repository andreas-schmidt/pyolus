AEOLUS_SRC := ../source

CXX := g++
CXXFLAGS := -fPIC -Wall -I/usr/include/python2.7 -I$(AEOLUS_SRC)

pyolus.so: pyolus.o addsynth.o
	$(CXX) -o $@ -shared $^ -lpython2.7 -lboost_python

addsynth.o: $(AEOLUS_SRC)/addsynth.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f *.o *.so
