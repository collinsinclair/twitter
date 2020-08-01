twitter: twitter.o user.o tweet.o
	g++ twitter.o user.o tweet.o -std=c++11 -o twitter

twitter.o: twitter.cpp
	g++ -c twitter.cpp -std=c++11

user.o: user.cpp user.h
	g++ -c user.cpp -std=c++11

tweet.o: tweet.cpp tweet.h
	g++ -c tweet.cpp -std=c++11

clean:
	rm *.o