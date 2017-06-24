/*** inside main thread of table ***/

char action;
action = players[i]->getPlay();
//....
//....
if (action == 'P')
    split(players[i]);

/***********************************/

void Table::split(Player* player)
{
    player->split(getCard(),getCard());
	char action;
    for (unsigned int i = 0; i < 2; i++)
    {
        action = player->getPlay(); //the player know what hand has to be played, because when the player stands it hands 0 to the vector containing the cards
        while (action != 'S')
        {
            if (action == 'H')
            {
                player->receiveCard(getCard());
            }
            else if (action == 'D')
            {
                player->receiveCard(getCard()); // the player already doubled it's money when getPlay() returned 'D'
            }
            else if (action == 'P')
            {
                split(player);
            }
            action = player->getPlay();
        }
    }
}



void Player::split(unsigned int card1, unsigned int card2);
    // puts card1 in first hand, and card2 in second hand
    // puts appropriate bets
