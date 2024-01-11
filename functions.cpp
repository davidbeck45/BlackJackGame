//
// Created 4/24/2020.
//
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <fstream>
#include "functions.h"
#include <iomanip>
#include <algorithm>

using namespace std;

// this is the function that creates the deck for the game. first loop is making the suite and the second is giving the number / face
vector<cards> createDeck(){
    vector<cards> deck;
    char suites[4] = {'S','H','D','C'};
    for(int i = 0; i < 4; ++i){
        for(int j = 1; j <= 13; j++ ){
            cards card;
            card.suite = suites[i];
            card.val = j;
            deck.push_back(card);
        }
    }
    return deck;
}
//this function is for picking the card from the deck at random and then getting rid of it like it would in the actual game.
functions::functions(vector<cards> &deck){
    int index = rand() % deck.size();
    val = deck[index].val;
    suite = deck[index].suite;
    deck.erase(deck.begin() + index);
}

/*
bool checkIfPlayerWins(int playerScore, int dealerScore){

    if(playerScore > 21) return false;

    if(dealerScore > 21) return true;


}*/
//this is for making the balance that the player will pull from to wager in games. first opening the folder and checking to see if it is succesful,
player::player(){
    double money;
    ifstream cin("bank.txt");
    if(cin.fail()){
        cerr << "Failed to open up bank role";
        cout << endl;
    }

    cin >> money;
    cin.close();
    bank = money;

}
//
int player::getBank() {
    return bank;
}
void player::changeBank(int newBank) {
    bank = newBank;
}
int player::getBet() {
    return bet;
}
// here we are taking the random number and the char that were drawn from the deck and displaying them to the player so they know what they have.
// we did this for the face cards because they were assigned to numbers and not king queen jack and ace.
void printCard(char suite, int val){
    if (suite == 'D'){
        if(val == 1){
            cout << "Ace of Diamonds";
        }else if(val >= 2 && val <= 10){
            cout << val << " of Diamonds";
        }else if(val == 11){
            cout << "Jack of Diamonds";
        }else if(val == 12){
            cout <<  "Queen of Diamonds";
        }else{
            cout << "King of Diamonds";
        }

    }else if(suite == 'H'){
        if (val == 1){
            cout << "Ace of Hearts";
        }else if(val >= 2 && val <= 10){
            cout << val << " of Hearts";
        }else if(val == 11){
            cout << "Jack of Hearts";
        }else if(val == 12){
            cout << "Queen of Hearts";
        }else{
            cout << "King of Hearts";
        }

    }else if(suite == 'C'){
        if (val == 1){
            cout << "Ace of Clubs";

        }else if(val >= 2 && val <= 10){
            cout << val << " of Clubs";

        }else if(val == 11){
            cout << "Jack of Clubs";

        }else if(val == 12){
            cout << "Queen of Clubs";

        }else{
            cout << "King of Clubs";

        }

    }else{
        if(val == 1){
            cout << "Ace of Spades";
        }else if(val >= 2 && val <= 10){
            cout << val << " of Spades";
        }else if(val == 11){
            cout << "Jack of Spades";

        }else if(val == 12){
            cout << "Queen of Spades";

        }else{
            cout << "King of Spades";
        }
    }
}

char functions::returnsuite() {
    return suite;
}
int functions::returnval() {
    return val;
}
string convertLower(string a) {
    string answer;
    for(int i = 0; i < a.size(); ++i){
        answer.push_back(tolower(a[i]));
    }
    return answer;
}
// this funciton will see if the user would like to draw another card. if they dont want to do this, then the turn will now go to the dealer.
// also we are making sure that no matter what the player puts in ( "Hit" "HIT" "hit") they will all register the command of hitting.
// this makes it easier for the user to play the game without worrying about how they type.
bool hitOrStay(){
    cout << "Hit or Stay" << endl;
    string answer;
    while(true){
        cin >> answer;
        if(convertLower(answer) == "hit"){
            return true;
        }else if(convertLower(answer) == "stay"){
            return false;
        }
        cout << "Hit or Stay?" << endl;
    }
    /*string answer;
    while(true){
        cin >> answer;
        if(answer == "hit"){
            return true;
        }else if(answer == "stay"){
            return false;
        }
        cout << "Hit or Stay?";
    }*/
}
// this function is for the dealer and play cards display, this is important because we dont want the player to know the second card that the dealer has.
void printCardsPreFlip(vector<functions> dealer,vector<functions> player){
    cout << "Dealers Cards:" << endl;
    printCard(dealer[0].returnsuite(), dealer[0].returnsuite());
    cout << endl << "unknown" << endl;
    cout << "Players cards:" << endl;
    for(int i = 0; i < player.size(); i++){
        printCard(player[i].returnsuite(), player[i].returnval());
        cout << endl;

    }
    cout << endl;
    /* printCard(player[0].returnsuite(), player[0].returnval());
     cout << endl;
     printCard(player[1].returnsuite(), player[1].returnval());
     cout << endl;*/

}


// this function is the same as the last but is a later phase in the game where the dealers cards will all be shown and same with the players
void printYourCards(vector<functions> dealer, vector<functions> player){
    cout << "Dealers Cards:" << endl;
    for(int i = 0; i < dealer.size(); ++i){
        printCard(dealer[i].returnsuite(), dealer[i].returnval());
        cout << endl;
    }
    cout << "Players cards:" << endl;
    for(int i = 0; i < player.size(); i++){
        printCard(player[i].returnsuite(), player[i].returnval());
        cout << endl;
    }
}
// here we will be finding the score of the cards and adding them together to get a number
int getScore(vector<functions> Cards) {
    vector<functions> sortedCards;

    /*vector<functions> sortedCards;
    sortedCards = Cards;
    vector<functions> usedForSorting;
    usedForSorting = Cards;
    int index;//sorting algorthim that didnt work :(
    int n;
    for(int i = 0; i < Cards.size(); ++i){
        n = usedForSorting[0].returnval();
        index = 0;
        for(int j = 0; j < usedForSorting.size(); ++i){

            if(usedForSorting[j].returnval() > n){
                n = usedForSorting[j].returnval();
                index = j;
            }

        }
        sortedCards.push_back(usedForSorting[index]);
        usedForSorting.erase(usedForSorting.begin() + index);
    }*/

    bool swap = true;//creates swap variable
    while(swap){
        swap = false;//if no swap occures it will break because that means it is sorted
        for( int i = 0; i < Cards.size() - 1; i++){
            if (Cards[i].returnval() < Cards[i + 1].returnval()){
                functions number = Cards[i];
                Cards[i] = Cards[i+1];
                Cards[i+1] = number;
                swap = true;
                }
        }
    }
    sortedCards = Cards;


    // this is one of the most important function that i stressed in the making of our game. here i wanted to make sure that the ace worked as intended.
    // as we all know the ace can be either 1 or 11 depending on the either cards that the player has. if 11 will cause the player or the dealer to lose the game,
    // it will now be  worth one. this, if done correctly can give the player or dealer a free hit, where it is impossible for them to go above 21.
    //Therefore the vector of the cards either player cards or dealers cards has to be sorted in desending order before adding up the score.
    int score = 0;
    for(int i = 0; i < sortedCards.size(); ++i){
        if(sortedCards[i].returnval() == 1){
            if ( score + 11 > 21){
                score += 1;
            }else{
                score += 11;
            }
        }else if(sortedCards[i].returnval() >= 11){
            score += sortedCards[i].returnval();

        }else{
            score += sortedCards[i].returnval();
        }

    }
    return score;
}

int playerbet(double bank){
    int bet;
    while(true){
        cin >> bet;
        if(bet >= 1){
            return bet;
        }
    }
}
// this function is the money maker in the game of BJ it makes sure to check if the player has a score of 21 at the start which gives them a blackjack.
// getting a blackjack is the reason why the game is "fair" for the player and not giving the house too much of an advantage.
bool checkIfBlackjack(vector<functions> Cards){
    int score = 0;
    for(int i = 0; i < Cards.size(); ++i){
        if(Cards[i].returnval() == 1){
            if ( score + 11 > 21){
                score += 1;
            }else{
                score += 11;
            }
        }else if(Cards[i].returnval() >= 11){
            score += Cards[i].returnval();

        }else{
            score += Cards[i].returnval();
        }

    }
    if (score == 21){
        return true;
    }else{
        return false;
    }
}