all: Strategy.o
	g++ -Wall -o prova Strategy.o StrategyMultiplier.o StrategySequence.o
		# because in this example I am using StrategyMultiplier and StrategySequence, otherwise there is no dependency
Strategy.o: PlayingStrategy.o StrategyMultiplier.o StrategySequence.o Strategy.cpp Strategy.hpp
	g++ -Wall -c Strategy.cpp
		# because in this example I am using StrategyMultiplier and StrategySequence, otherwise there is no dependency
PlayingStrategy.o: PlayingStrategy.cpp PlayingStrategy.hpp
	g++ -Wall -c PlayingStrategy.cpp


StrategySequence.o: StrategySequence.cpp StrategySequence.hpp
	g++ -Wall -c StrategySequence.cpp
StrategyMultiplier.o: StrategyMultiplier.cpp StrategyMultiplier.hpp
	g++ -Wall -c StrategyMultiplier.cpp
	
clean:
	rm *.o
