all: test 

clean:
	rm -f *.exe *.o

test: clean
	g++ test.cpp -o test.exe -O3 -lmysqlcppconn -std=c++17
	
