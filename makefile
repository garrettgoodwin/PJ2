all: test2

test2: test2.o program2.o programFile.o token.o tokenList.o tokenType.o util.o parser.o
	g++ -o test2 test2.o program2.o programFile.o token.o tokenList.o tokenType.o util.o parser.o

test2.o: test2.cpp
	g++ -c test2.cpp

program2.o: program2.cpp
	g++ -c program2.cpp

programFile.o: programFile.cpp
	g++ -c programFile.cpp

token.o: token.cpp
	g++ -c token.cpp

tokenList.o: tokenList.cpp
	g++ -c tokenList.cpp

tokenType.o: tokenType.cpp
	g++ -c tokenType.cpp

util.o: util.cpp
	g++ -c util.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

clean:
	rm -f test2 *.o

run: test2
	./test2