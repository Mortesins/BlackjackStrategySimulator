#ifndef RULES_HPP
#define RULES_HPP

using namespace std;

#include <vector>

class Rules
{
  private:
    bool aces;
    unsigned handsAfterAceSplit;
    bool bjBjPush;
  public:
    Rules();
    
    vector <char> getActionsNotAllowed(const vector <vector <unsigned short> > & cards, unsigned handIndex);
    bool blackjackBlackjackPush();
};

#endif
