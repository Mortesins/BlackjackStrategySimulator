all:
	$(MAKE) bjsim

bjsim: Test.cpp Table.o PlayerSeat.o Shoe.o Dealer.o Rules.o CountingSystems/HiOpt1.o Action.o Player.o Constants.o Strategy/Strategy_all.o
	g++ -Wall -o bjsim Test.cpp Table.o PlayerSeat.o Shoe.o Dealer.o Rules.o CountingSystems/HiOpt1.o Action.o Player.o Constants.o Strategy/Strategy_all.o

Table.o: Table.cpp Table.hpp
	g++ -g -Wall -c Table.cpp
PlayerSeat.o: PlayerSeat.cpp PlayerSeat.hpp
	g++ -g -Wall -c PlayerSeat.cpp
Shoe.o: Shoe.cpp Shoe.hpp
	g++ -Wall -c Shoe.cpp
Dealer.o: Dealer.cpp Dealer.hpp
	g++ -Wall -c Dealer.cpp
Rules.o: Rules.cpp Rules.hpp
	g++ -Wall -c Rules.cpp
CountingSystems/HiOpt1.o: CountingSystems/HiOpt1.cpp CountingSystems/HiOpt1.hpp
	g++ -Wall -c CountingSystems/HiOpt1.cpp -o CountingSystems/HiOpt1.o
Player.o: Player.cpp Player.hpp
	g++ -g -Wall -c Player.cpp
Action.o: Action.cpp Action.hpp
	g++ -Wall -c Action.cpp
Constants.o: Constants.cpp Constants.hpp
	g++ -g -Wall -c Constants.cpp
Strategy/Strategy_all.o: $(shell find Strategy/ | grep ".cpp\|.hpp")
	$(MAKE) -C Strategy/

Tests/testDealer: Tests/TestDealer.cpp Dealer.o
	g++ -Wall -o Tests/testDealer Tests/TestDealer.cpp Dealer.o -lgtest -lgtest_main -lpthread
Tests/testRules: Tests/TestRules.cpp Rules.o Action.o
	g++ -Wall -o Tests/testRules Tests/TestRules.cpp Rules.o Action.o -lgtest -lgtest_main -lpthread
Tests/testShoe: Tests/TestShoe.cpp Shoe.o
	g++ -Wall -o Tests/testShoe Tests/TestShoe.cpp Shoe.o -lgtest -lgtest_main -lpthread
Tests/testTable: Tests/TestTable.cpp Table.o PlayerSeat.o Shoe.o Dealer.o Rules.o CountingSystems/HiOpt1.o Action.o Player.o Constants.o Strategy/Strategy_all.o
	g++ -Wall -o Tests/testTable Tests/TestTable.cpp Table.o PlayerSeat.o Shoe.o Dealer.o Rules.o CountingSystems/HiOpt1.o Action.o Player.o Constants.o Strategy/Strategy_all.o -lgtest -lgtest_main -lpthread

clean:
	$(MAKE) -C Strategy/ clean
	rm *.o || echo "Already removed *.o"
	rm *.gch || echo "Already removed *.gch"
cleantest:
	$(MAKE) -C Strategy/ cleantest
	rm Tests/test*
cleanall:
	$(MAKE) clean
	$(MAKE) cleantest
test: Tests/testDealer Tests/testRules Tests/testShoe Tests/testTable
	chmod u+x Tests/test*
	for i in `ls Tests | grep test`; do ./Tests/$$i; done
testall:
	$(MAKE) test
	$(MAKE) -C Strategy/ test
