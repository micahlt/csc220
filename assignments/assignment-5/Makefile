all: url_test

url_test: URLDriver.o url.o
	g++ URLDriver.o url.o -o url_test

URLDriver.o: URLDriver.cpp
	g++ -c URLDriver.cpp

url.o: url.cpp url.h
	g++ -c url.cpp url.h

clean:
	rm -rf *.o *.h.gch url_test