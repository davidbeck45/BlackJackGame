#include <iostream>
#include <ctime>
#include "functions.h"
#include <iomanip>
#include <algorithm>
#include <fstream>


using namespace std;


int main() {

    srand(time(0));     //seeding the random function
    player user;
    cout << "You have " << user.getBank() << " dollars in the bank" << endl; // telling player their balance
    if(user.getBank() == 0){  //this will see if the player is out of money in the file/ bank if so the house will give them 10 chips to keep playing
        user.changeBank(10);
        cout << "You were out of money so you were given $10.00." << endl;
    }
    cout << "We'll convert your money to chips each chip is equil to 1 dollar." << endl << endl; // telling user that the chips are worth a dollar
    cout << "You have " << user.getBank() << " dollars in the bank" << endl;
    vector<cards> deck = createDeck(); // creation of the deck
    bool playAgain = true; // first making sure that the game runs when started this is done by initalizing it to true
    while(playAgain){ // asking if the user would like to play agian at the end makes sure that the game keeps going and that they have the same bank balance
        int bet; // if play agian is true, then the game runs in this loop.

        cout << "place you bet (min of $1)" << endl;
        bet = playerbet(user.getBank());
        user.changeBank(user.getBank() - bet);

        vector<functions> playersCards;
        vector<functions> dealersCards;
        functions pc1(deck), pc2(deck), dcd(deck), dcu(deck);
        playersCards.push_back(pc1);
        playersCards.push_back(pc2);
        dealersCards.push_back(dcd);
        dealersCards.push_back(dcu);
        cout << "You are delt a ";
        printCard(pc1.returnsuite(), pc1.returnval());
        cout << endl << "The dealer places a card face down" << endl;
        cout << "You are delt a ";
        printCard(pc2.returnsuite(), pc2.returnval());
        cout << endl <<  "The dealer places a ";
        printCard(dcu.returnsuite(), dcu.returnval());
        cout << " face up" << endl << endl;

        if(checkIfBlackjack(playersCards)){
            cout << "Blackjack Player wins" << endl;
            user.changeBank(user.getBank() + bet * 3 );
            // CHANGE SCORE FOR BLACKJACK

        }else {

            printCardsPreFlip(dealersCards, playersCards);

            //BREAKS HERE NEED TO FIX
            bool playerlost = false;
            while (hitOrStay()) {

                functions pc3(deck);
                cout << "The dealer hits you with a ";
                printCard(pc3.returnsuite(), pc3.returnval());
                cout << endl;
                playersCards.push_back(pc3);
                printCardsPreFlip(dealersCards, playersCards);
                if (getScore(playersCards) > 21) {
                    playerlost = true;
                    break;
                }
            }
            if (playerlost) {
                cout << "You went over 21 you loose." << endl;

            } else {

                cout << "The dealer flips over his other card" << endl;
                printCard(dealersCards[1].returnsuite(), dealersCards[1].returnval());
                cout << endl << endl;
                printYourCards(dealersCards, playersCards);
                if (getScore(dealersCards) > getScore(playersCards)) {
                    cout << "Dealer wins, you loose " << bet << " chips" << endl;
                } else if (getScore(playersCards) > getScore(dealersCards)) {
                    /*cout << "The dealer desides to hit." << endl;
                    functions newcard(deck);//Need to check if infinite loop
                    cout << "The dealer is delt a card" << endl;
                    printCard(newcard.returnsuite(), newcard.returnval());
                    cout << endl;
                    dealersCards.push_back(newcard);*/

                    while (true) {
                        cout << "The dealer desides to hit." << endl;
                        functions newcard(deck);//Need to check if infinite loop
                        cout << "The dealer is delt a card" << endl;
                        printCard(newcard.returnsuite(), newcard.returnval());
                        cout << endl;
                        dealersCards.push_back(newcard);

                        if (getScore(dealersCards) >= getScore(playersCards) || getScore(dealersCards) > 21) {
                            break;
                        }
                    }
                    if (getScore(dealersCards) > 21) {
                        cout << "The dealer busted! Player wins." << endl;
                        user.changeBank(user.getBank() + bet * 2);
                        //PUT IF PLAYER WINS EDIT THE MONEY EARNED

                    }else if (getScore(dealersCards) == getScore(playersCards)) {
                        cout << "The dealer has decided to not hit, push." << endl;
                        user.changeBank(user.getBank() + bet);
                        //PUT IF TIE EDIT

                    }else if (getScore(dealersCards) > getScore(playersCards)){
                        cout << "The dealer has a higher count, You loose." << endl;
                    }

                } else if (getScore(dealersCards) == getScore(playersCards)) {
                    cout << "The dealer has decided to not hit, push." << endl;
                    user.changeBank(user.getBank() + bet);
                }

            }
        }



// here is where the player chooses if they would like to play again
        cout << "You have " << user.getBank() << " dollars in the bank" << endl;
        char redo;
        cout << endl << endl << "Do you want to play another hand?(Y/N)?" << endl;
        cin >> redo;
        bet = 0;
        if(redo == 'Y' or redo == 'y'){
            playAgain = true;
        }else{
            playAgain = false;
        }

    }

    cout << "Thank you for playing. Your winnings will be transferred to your bank." << endl;
    ofstream fout("bank.txt"); // money is transfered to the balance in the file
    if(fout.fail()){
        cerr << "failed return value to bank open bank" << endl;
        return -1;
    }
    fout << user.getBank();
    fout.close();



    return 0;
}