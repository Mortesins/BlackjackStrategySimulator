Strategy_all.o: PlayingStrategy.o StrategyMultiplier.o StrategySequence.o StopStrategy.o Strategy.o
	ld -r -o Strategy_all.o Strategy.o StrategyMultiplier.o StrategySequence.o StopStrategy.o PlayingStrategy.o
		# because in this example I am using StrategyMultiplier and StrategySequence, otherwise there is no dependency

Strategy.o: Strategy.cpp Strategy.hpp PlayingStrategy.o StopStrategy.o
	g++ -Wall -c Strategy.cpp
PlayingStrategy.o: PlayingStrategy.cpp PlayingStrategy.hpp
	g++ -Wall -c PlayingStrategy.cpp
StopStrategy.o: StopStrategy.cpp StopStrategy.hpp
	g++ -Wall -c StopStrategy.cpp


StrategySequence.o: StrategySequence.cpp StrategySequence.hpp Strategy.o
	g++ -Wall -c StrategySequence.cpp
StrategyMultiplier.o: StrategyMultiplier.cpp StrategyMultiplier.hpp Strategy.o
	g++ -Wall -c StrategyMultiplier.cpp
	

all: Strategy_all.o
test: StrategyTest.cpp Strategy_all.o
	g++ -Wall -o prova StrategyTest.cpp Strategy_all.o
clean:
	rm *.o || echo "Already removed *.o"
