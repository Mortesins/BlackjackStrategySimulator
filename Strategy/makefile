Strategy_all.o: BasicPlayingStrategy.o StrategyMultiplier.o StrategySequence.o StopStrategy.o Strategy.o
	ld -r -o Strategy_all.o Strategy.o StrategyMultiplier.o StrategySequence.o StopStrategy.o PlayingStrategy.o BasicPlayingStrategy.o
		# because in this example I am using StrategyMultiplier and StrategySequence, otherwise there is no dependency
		# I am using BasicPlayingStrategy

Strategy.o: Strategy.cpp Strategy.hpp PlayingStrategy.o StopStrategy.o
	g++ -g -Wall -c Strategy.cpp
PlayingStrategy.o: PlayingStrategy.cpp PlayingStrategy.hpp
	g++ -g -Wall -c PlayingStrategy.cpp
BasicPlayingStrategy.o: BasicPlayingStrategy.cpp BasicPlayingStrategy.hpp PlayingStrategy.o
	g++ -g -Wall -c BasicPlayingStrategy.cpp
IndexedPlayingStrategy.o: IndexedPlayingStrategy.cpp IndexedPlayingStrategy.hpp BasicPlayingStrategy.o
	g++ -g -Wall -c IndexedPlayingStrategy.cpp
StopStrategy.o: StopStrategy.cpp StopStrategy.hpp
	g++ -Wall -c StopStrategy.cpp


StrategySequence.o: StrategySequence.cpp StrategySequence.hpp Strategy.o
	g++ -Wall -c StrategySequence.cpp
StrategyMultiplier.o: StrategyMultiplier.cpp StrategyMultiplier.hpp Strategy.o
	g++ -Wall -c StrategyMultiplier.cpp

Tests/testBasicPlayingStrategy: Tests/TestBasicPlayingStrategy.cpp BasicPlayingStrategy.o
	g++ -Wall -o Tests/testBasicPlayingStrategy Tests/TestBasicPlayingStrategy.cpp  BasicPlayingStrategy.o PlayingStrategy.o ../Action.cpp -lgtest -lgtest_main -lpthread
Tests/testIndexedPlayingStrategy: Tests/TestIndexedPlayingStrategy.cpp IndexedPlayingStrategy.o
	g++ -Wall -o Tests/testIndexedPlayingStrategy Tests/TestIndexedPlayingStrategy.cpp IndexedPlayingStrategy.o BasicPlayingStrategy.o PlayingStrategy.o ../Action.cpp -lgtest -lgtest_main -lpthread
Tests/testStopStrategy: Tests/TestStopStrategy.cpp StopStrategy.o
	g++ -Wall -o Tests/testStopStrategy Tests/TestStopStrategy.cpp StopStrategy.o -lgtest -lgtest_main -lpthread
Tests/testStrategyMultiplier: Tests/TestStrategyMultiplier.cpp StrategyMultiplier.o
	g++ -Wall -o Tests/testStrategyMultiplier Tests/TestStrategyMultiplier.cpp StrategyMultiplier.o Strategy.o BasicPlayingStrategy.o PlayingStrategy.o StopStrategy.o ../Action.cpp -lgtest -lgtest_main -lpthread

all: Strategy_all.o
#test: StrategyTest.cpp Strategy_all.o
#	g++ -Wall -o prova StrategyTest.cpp Strategy_all.o
test: Tests/testBasicPlayingStrategy Tests/testIndexedPlayingStrategy Tests/testStopStrategy Tests/testStrategyMultiplier
	chmod u+x Tests/test*
	for i in `ls Tests | grep test`; do ./Tests/$$i; done
clean:
	rm *.o || echo "Already removed *.o"
cleantest:
	rm Tests/test*
