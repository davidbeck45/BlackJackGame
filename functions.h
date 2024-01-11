//
// Created 4/30/2020.
//

#ifndef COMMENTSFINALPROJECT_FUNCTIONS_H
#define COMMENTSFINALPROJECT_FUNCTIONS_H

#include <iostream>
#include <vector>
using namespace std;


class cards{
public:
    int val;
    char suite;
};


class functions {
public:
    functions(vector<cards> &deck);
    char returnsuite();
    int returnval();

private:
    int val;
    char suite;


};

class player{
public:
    player();
    int getBank();
    void changeBank(int newBank);
    int getBet();




private:
    int bank;
    int bet;
    int playerScore;
    int dealerScore;


};


vector<cards> createDeck();
void printCard(char suite, int val);
bool hitOrStay();
string convertLower(string converter);
void printCardsPreFlip(vector<functions> dealer,vector<functions> player);
void printYourCards(vector<functions> dealer, vector<functions> player);
int playerbet(double bank);
bool checkIfBlackjack(vector<functions> Cards);
int getScore(vector<functions> playerCards);





#endif //COMMENTSFINALPROJECT_FUNCTIONS_H
