CXXFLAGS += --std=c++17



all: threads



debug: CXXFLAGS += -g

debug: threads



threads: main.o Threadpool.o Factorial.o *.h

	$(CXX) $(CXXFLAGS) main.o Threadpool.o Factorial.o -o threads



main.o: main.cpp *.h

	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o



Threadpool.o: Threadpool.cpp *.h

	$(CXX) $(CXXFLAGS) -c Threadpool.cpp -o Threadpool.o



Factorial.o: Factorial.cpp *.h

	$(CXX) $(CXXFLAGS) -c Factorial.cpp -o Factorial.o



clean:

	rm -f *.o *.gch threads