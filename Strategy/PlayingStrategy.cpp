#include "PlayingStrategy.hpp"

#include <iostream>

PlayingStrategy::PlayingStrategy()
{
    /*** ORDER OF ACTIONS ***/
        // first check surrender, if not check split, then double down, then hit stand
    orderOfActions[0] = 'R';
    orderOfActions[1] = 'P';
    orderOfActions[2] = 'D';
    orderOfActions[3] = 'H';
    /************************/
    // 2 3 4 5 6 7 8 9 10 A                         COLUMNS
    // 8 9 10 11 12 13 14 15 16 17                  ROWS
    // 2-2 3-3 4-4 5-5 6-6 7-7 8-8 9-9 10-10 A-A    ROWS
    // A2 A3 A4 A5 A6 A7 A8 A9                      ROWS
    /*** HIT STAND ***/
    bool tmpHitStand[28][10] = 
        {
            // 2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |  A  |  
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 8
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 9
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 10
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 11
            {true ,true ,false,false,false,true ,true ,true ,true ,true }, // 12
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 13
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 14
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 15
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 16
            {false,false,false,false,false,false,false,false,false,false}, // 17
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 2-2
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 3-3
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 4-4
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 5-5
            {true ,true ,false,false,false,true ,true ,true ,true ,true }, // 6-6
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 7-7
            {false,false,false,false,false,true ,true ,true ,true ,true }, // 8-8
            {false,false,false,false,false,false,false,false,false,false}, // 9-9
            {false,false,false,false,false,false,false,false,false,false}, // 10-10
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A-A
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A2
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A3
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A4
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A5
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A6
            {false,false,false,false,false,false,false,true ,true ,true }, // A7
            {false,false,false,false,false,false,false,false,false,false}, // A8
            {false,false,false,false,false,false,false,false,false,false}, // A9
        };
    for (unsigned i = 0; i < 10; i++)
    {
        for (unsigned j = 0; j < 28; j++)
        {
            hitStand[j][i] = tmpHitStand[j][i];
        }
    }
    /*****************/
    
    /*** SPLIT ***/
    bool tmpSplit[10][10] = 
    {
        // 2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |  A  |  
        {true ,true ,true ,true ,true ,true ,false,false,false,false}, // 2-2
        {true ,true ,true ,true ,true ,true ,false,false,false,false}, // 3-3
        {false,false,false,true ,true ,false,false,false,false,false}, // 4-4
        {false,false,false,false,false,false,false,false,false,false}, // 5-5
        {true ,true ,true ,true ,true ,false,false,false,false,false}, // 6-6
        {true ,true ,true ,true ,true ,true ,false,false,false,false}, // 7-7
        {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // 8-8
        {true ,true ,true ,true ,true ,false,true ,true ,false,false}, // 9-9
        {false,false,false,false,false,false,false,false,false,false}, // 10-10
        {true ,true ,true ,true ,true ,true ,true ,true ,true ,true }, // A-A
    };

    for (unsigned i = 0; i < 10; i++)
    {
        for (unsigned j = 0; j < 10; j++)
        {
            split[j][i] = tmpSplit[j][i];
        }
    }
    /*************/
    
    /*** DOUBLE DOWN ***/
    bool tmpDoubleDown[28][10] = 
        {
            // 2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |  A  |  
            {false,false,false,false,false,false,false,false,false,false}, // 8
            {false,true ,true ,true ,true ,false,false,false,false,false}, // 9
            {true ,true ,true ,true ,true ,true ,true ,true ,false,false}, // 10
            {true ,true ,true ,true ,true ,true ,true ,true ,true ,false}, // 11
            {false,false,false,false,false,false,false,false,false,false}, // 12
            {false,false,false,false,false,false,false,false,false,false}, // 13
            {false,false,false,false,false,false,false,false,false,false}, // 14
            {false,false,false,false,false,false,false,false,false,false}, // 15
            {false,false,false,false,false,false,false,false,false,false}, // 16
            {false,false,false,false,false,false,false,false,false,false}, // 17
            {false,false,false,false,false,false,false,false,false,false}, // 2-2
            {false,false,false,false,false,false,false,false,false,false}, // 3-3
            {false,false,false,false,false,false,false,false,false,false}, // 4-4
            {true ,true ,true ,true ,true ,true ,true ,true ,false,false}, // 5-5
            {false,false,false,false,false,false,false,false,false,false}, // 6-6
            {false,false,false,false,false,false,false,false,false,false}, // 7-7
            {false,false,false,false,false,false,false,false,false,false}, // 8-8
            {false,false,false,false,false,false,false,false,false,false}, // 9-9
            {false,false,false,false,false,false,false,false,false,false}, // 10-10
            {false,false,false,false,true ,false,false,false,false,false}, // A-A
            {false,false,false,false,true ,false,false,false,false,false}, // A2
            {false,false,false,true ,true ,false,false,false,false,false}, // A3
            {false,false,true ,true ,true ,false,false,false,false,false}, // A4
            {false,false,true ,true ,true ,false,false,false,false,false}, // A5
            {false,true ,true ,true ,true ,false,false,false,false,false}, // A6
            {false,true ,true ,true ,true ,false,false,false,false,false}, // A7
            {false,false,false,false,false,false,false,false,false,false}, // A8
            {false,false,false,false,false,false,false,false,false,false}, // A9
        };
    for (unsigned i = 0; i < 10; i++)
    {
        for (unsigned j = 0; j < 28; j++)
        {
            doubleDown[j][i] = tmpDoubleDown[j][i];
        }
    }

    /*******************/
    
    /*** SURRENDER ***/
    for (unsigned i = 0; i < 10; i++)
    {
        for (unsigned j = 0; j < 28; j++)
        {
            surrender[j][i] = false;
        }
    }
    /****************/
}

char PlayingStrategy::getPlay(const vector <unsigned short>& cards, unsigned short dealerUpCard, vector <char> actionsNotAllowed) const
{
    // order in which I check the actions depends on "orderOfActions"
    char action;
    char play = '\0';
    bool actionFound;
    unsigned j;
    vector <unsigned short> coord = getCoordinates(cards,dealerUpCard);
    
    unsigned i = 0; 
    while (i < 4 && play == '\0')
    {
        action = orderOfActions[i];
        
        /*** find action inside actionsNotAllowed ***/
        actionFound = false;
        j = 0;
        while (j < actionsNotAllowed.size() && !actionFound)
        {
            if (toupper(actionsNotAllowed[j]) == action) 
                actionFound = true;
            else //so that I have the ace position in i
                j++;
        }
        /********************************************/
        /* debug
        cout << action << " " << actionFound << endl;
        */
        if (!actionFound) //if action is allowed, so it is not inside actionsNotAllowed
        {
            switch(action)
            {
                case 'R':
                    if (surrender[coord[0]][coord[1]]) // if for that hand I have to surrender than it is true
                        play = 'R';
                    // NOTE: if false, than while loop iteration finishes, so the next action is considered
                    break;
                case 'P':
                    if (coord[0] >= 10 && coord[0] <= 19)
                    {
                        if (split[coord[0]-10][coord[1]])
                            play = 'P';
                    }
                    break;
                case 'D':
                    if (doubleDown[coord[0]][coord[1]])
                        play = 'D';
                    break;
                case 'H':
                    if (hitStand[coord[0]][coord[1]])
                        play = 'H';
                    else
                        play = 'S';
                    break;
            }
        }
        
        i++;
    }
    return play;
}

char PlayingStrategy::getPlay(const vector <unsigned short>& cards, unsigned short dealerUpCard) const  //redundant 
{
    vector <char> tmp;
    return getPlay(cards,dealerUpCard,tmp);
}

vector <unsigned short> PlayingStrategy::getCoordinates(const vector <unsigned short>& cards, unsigned short dealerUpCard) const
{
    // first element row == player hand, second element column == dealerUpCard
    vector <unsigned short> coord;
    unsigned row = 0;
    /*** player hand ***/
    // if two cards
        // check for pair
    // if not pair
        // check for ace
        // otherwise sum
    if (cards.size() == 2 && cards[0] == cards[1])
    {
        // 2-2 10, A-A 19
        if (cards[0] == 1) //ACE
            row = 19;
        else
            row = 8 + cards[0]; // 2-2 --> 10
    }
    
    if (row == 0) // no pair
    {
        unsigned sum = 0;
     
        bool aceFound = false;
        unsigned i = 0;
        while (i < cards.size() && !aceFound)
        {
            if (cards[i] == 1) 
                aceFound = true;
            else //so that I have the ace position in i
                i++;
        }
        
        if (aceFound)
        {
            for (unsigned j = 0; j < cards.size(); j++)
            {
                if (j != i)
                    sum += cards[j];
            }
            // sum = 2 --> 20
            if (sum <= 9)
                row = sum + 18;
                    //NOTE: if sum > 9, there is an ace but it is not soft hand because it is ace + something bigger than 9
            else if (sum == 10)
                row = 9;
                // if sum == 10, it is either blackjack, so the function would not be called, or 21, so it would follow 17 or higher rule 
        }
        
        if (row == 0) // ace not found or not a soft hand
        { // sum all cards
            if (aceFound)
                sum += 1; //because it is not soft hand, already summed all cards except for one ace
            else
            {
                for (unsigned j = 0; j < cards.size(); j++)
                {
                    sum += cards[j];
                }
            }
            
            if (sum <= 8)
                row = 0;
            else if (sum >= 17)
                row = 9;
            else
                row = sum - 8; // so if 9 --> 1 which is second row
        }
    }
    
    coord.push_back(row);
    /*******************/
    /*** dealer hand ***/
    if (dealerUpCard == 1) // ace
        coord.push_back(9); //last column
    else    
        coord.push_back(dealerUpCard - 2 ); // 2 is first column so 0
    /*******************/
    
    return coord;
}

void PlayingStrategy::printStrategy() const
{

    for (unsigned j = 0; j < 10; j++)
    {
        cout << j << " ";
        for (unsigned i = 0; i < 9; i++)
        {
            if (surrender[j][i])
                cout << "R,";
            else if (doubleDown[j][i])
                cout << "D,";
            else if (hitStand[j][i])
                cout << "H,";
            else
                cout << "S,";
        }
        if (surrender[j][9])
            cout << "R" << endl;
        else if (doubleDown[j][9])
            cout << "D" << endl;
        else if (hitStand[j][9])
            cout << "H" << endl;
        else
            cout << "S" << endl;
    }
    cout << "---------------------" << endl;
    unsigned k = 0;
    for (unsigned j=10; j < 20; j++)
    {
        cout << j << " ";
        for (unsigned i = 0; i < 9; i++)
        {
            if (surrender[j][i])
                cout << "R,";
            else if (split[k][i])
                cout << "P,";
            else if (doubleDown[j][i])
                cout << "D,";
            else if (hitStand[j][i])
                cout << "H,";
            else
                cout << "S,";
        }
        if (surrender[j][9])
            cout << "R" << endl;
        else if (split[k][9])
            cout << "P" << endl;
        else if (doubleDown[j][9])
            cout << "D" << endl;
        else if (hitStand[j][9])
            cout << "H" << endl;
        else
            cout << "S" << endl;
        k++;
    }
    cout << "---------------------" << endl;
    for (unsigned j=20; j < 28; j++)
    {
        cout << j << " ";
        for (unsigned i = 0; i < 9; i++)
        {
            if (surrender[j][i])
                cout << "R,";
            else if (doubleDown[j][i])
                cout << "D,";
            else if (hitStand[j][i])
                cout << "H,";
            else
                cout << "S,";
        }
        if (surrender[j][9])
            cout << "R" << endl;
        else if (doubleDown[j][9])
            cout << "D" << endl;
        else if (hitStand[j][9])
            cout << "H" << endl;
        else
            cout << "S" << endl;
    }
}

