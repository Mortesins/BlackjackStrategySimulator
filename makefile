all: Test.cpp Table.o
	g++ -Wall -o prova Test.cpp Table_all.o Player.o Strategy/Strategy_all.o
	
Table.o: Table.cpp Table.hpp PlayerSeat.o Shoe.o Dealer.o Rules.o CountingSystem.o
	g++ -Wall -c Table.cpp
	ld -r -o Table_all.o PlayerSeat.o Shoe.o Dealer.o Rules.o CountingSystem.o
PlayerSeat.o: PlayerSeat.cpp PlayerSeat.hpp Player.o
	g++ -Wall -c PlayerSeat.cpp
Shoe.o: Shoe.cpp Shoe.hpp
	g++ -Wall -c Shoe.cpp
Dealer.o: Dealer.cpp Dealer.hpp
	g++ -Wall -c Dealer.cpp
Rules.o: Rules.cpp Rules.hpp
	g++ -Wall -c Rules.cpp
CountingSystem.o: CountingSystem.cpp CountingSystem.hpp
	g++ -Wall -c CountingSystem.cpp

Player.o: Player.cpp Player.hpp Strategy/Strategy_all.o
	g++ -Wall -c Player.cpp
Strategy/Strategy_all.o: $(shell find Strategy/ | grep ".cpp\|.hpp")
	$(MAKE) -C Strategy/
clean:
	$(MAKE) -C Strategy/ clean
	rm *.o || echo "Already removed *.o"
	rm *.gch || echo "Already removed *.gch"
