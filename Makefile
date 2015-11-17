all:
	g++ -c Card.cpp Deck.cpp -std=c++0x
	g++ Sim.cpp Card.o Deck.o -o Sim -std=c++0x
