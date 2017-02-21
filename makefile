gotofail: gotofail.cpp
	g++ -o gotofail -Wall -std=c++11 gotofail.cpp


run: gotofail
	./gotofail

test: gotofail
	./gotofail testing

clean:
	rm -f gotofail