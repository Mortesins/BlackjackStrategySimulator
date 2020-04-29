all: Test.cpp Table.o
	g++ -Wall -o prova Test.cpp Table_all.o Player.o Strategy/Strategy_all.o

Table.o: Table.cpp Table.hpp PlayerSeat.o Shoe.o Dealer.o Rules.o HiOpt1.o Action.o
	g++ -g -Wall -c Table.cpp
	ld -r -o Table_all.o Table.o PlayerSeat.o Shoe.o Dealer.o Rules.o CountingSystems/HiOpt1.o Action.o
PlayerSeat.o: PlayerSeat.cpp PlayerSeat.hpp Player.o
	g++ -g -Wall -c PlayerSeat.cpp
Shoe.o: Shoe.cpp Shoe.hpp
	g++ -Wall -c Shoe.cpp
Dealer.o: Dealer.cpp Dealer.hpp
	g++ -Wall -c Dealer.cpp
Rules.o: Rules.cpp Rules.hpp
	g++ -Wall -c Rules.cpp
HiOpt1.o: CountingSystems/HiOpt1.cpp CountingSystems/HiOpt1.hpp
	g++ -Wall -c CountingSystems/HiOpt1.cpp -o CountingSystems/HiOpt1.o
Action.o: Action.cpp Action.hpp
	g++ -Wall -c Action.cpp
Player.o: Player.cpp Player.hpp Strategy/Strategy_all.o
	g++ -g -Wall -c Player.cpp
Strategy/Strategy_all.o: $(shell find Strategy/ | grep ".cpp\|.hpp")
	$(MAKE) -C Strategy/

Tests/testDealer: Tests/TestDealer.cpp Dealer.o
	g++ -Wall -o Tests/testDealer Tests/TestDealer.cpp Dealer.o -lgtest -lgtest_main -lpthread

clean:
	$(MAKE) -C Strategy/ clean
	rm *.o || echo "Already removed *.o"
	rm *.gch || echo "Already removed *.gch"
test: Tests/testDealer
	chmod u+x Tests/test*
	for i in `ls Tests | grep test`; do ./Tests/$$i; done
testall:
	$(MAKE) test
	$(MAKE) -C Strategy/ test
