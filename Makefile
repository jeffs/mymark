CXXFLAGS = -std=c++1z -pedantic -Wall -Wextra -Wno-c99-extensions -ftrapv -O3
CPPFLAGS = -isystem $(HOME)/Documents/pkg/GSL/include
LDFLAGS = -lcmark

main: main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

install: main
	cp $< $(HOME)/bin/mymark

main.s: main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -S -o $@ $<
	c++filt <$@ |sponge $@

main.ii: main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -E -o $@ $<

main.o: main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f main *.o *.ii *.s

.PHONY: run
run: main
	./main

.PHONY: test
test: main
	./main

