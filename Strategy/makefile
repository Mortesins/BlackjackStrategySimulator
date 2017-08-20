all: StrategyTest.cpp PlayingStrategy.o StrategyMultiplier.o StrategySequence.o StopStrategy.o Strategy.o
	g++ -Wall -o prova StrategyTest.cpp Strategy.o StrategyMultiplier.o StrategySequence.o StopStrategy.o PlayingStrategy.o
		# because in this example I am using StrategyMultiplier and StrategySequence, otherwise there is no dependency
Strategy.o: Strategy.cpp Strategy.hpp
	g++ -Wall -c Strategy.cpp
PlayingStrategy.o: PlayingStrategy.cpp PlayingStrategy.hpp
	g++ -Wall -c PlayingStrategy.cpp
StopStrategy.o: StopStrategy.cpp StopStrategy.hpp
	g++ -Wall -c StopStrategy.cpp


StrategySequence.o: StrategySequence.cpp StrategySequence.hpp
	g++ -Wall -c StrategySequence.cpp
StrategyMultiplier.o: StrategyMultiplier.cpp StrategyMultiplier.hpp
	g++ -Wall -c StrategyMultiplier.cpp
	
clean:
	rm *.o
