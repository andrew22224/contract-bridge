#include <iostream>
#include <iomanip>

#include "card.h"
#include "random.h"
#include "deck.h"
#include "hand.h"
#include "game.h"

using namespace std;

// Constants
const int NUM_CARDS = 10;

/*int main() {
	/*Deck deck;
	deck.shuffle();
	Hand hand = Hand();
	for (int i = 0; i < 13; i++) {
        Card* pCard = deck.dealNextCard();
        hand.addCard(pCard);
	}
	hand.doStuff();*/
	/*Game game;
	Hand hand;
	Card* card = new Card(SEVEN, DIAMONDS);
	Card* card1 = new Card(NINE, SPADES);
	Card* card2 = new Card(THREE, DIAMONDS);
	Card* card3 = new Card(FIVE, DIAMONDS);
	Card* card4 = new Card(ACE, HEARTS);
	Card* card5 = new Card(TWO, DIAMONDS);
	hand.addCard(card);
	hand.addCard(card1);
	hand.addCard(card2);
	hand.addCard(card3);
	hand.addCard(card4);
	hand.addCard(card5);
	Hand hand1;
	Card* card6 = new Card(SEVEN, DIAMONDS);
	Card* card7 = new Card(SIX, SPADES);
	Card* card8 = new Card(THREE, DIAMONDS);
	Card* card9 = new Card(FIVE, SPADES);
	hand1.addCard(card6);
	hand1.addCard(card7);
	hand1.addCard(card8);
	hand1.addCard(card9);
	Hand hand2;
	Card* card10 = new Card(SEVEN, DIAMONDS);
	Card* card11 = new Card(SIX, SPADES);
	Card* card12 = new Card(THREE, DIAMONDS);
	Card* card13 = new Card(FIVE, SPADES);
	hand2.addCard(card10);
	hand2.addCard(card11);
	hand2.addCard(card12);
	hand2.addCard(card13);
	Hand hand3;
	Card* card14 = new Card(SEVEN, CLUBS);
	Card* card15 = new Card(SIX, CLUBS);
	hand3.addCard(card14);
	hand3.addCard(card15);
    game.hands[0] = &hand;
    game.hands[1] = &hand1;
    game.hands[2] = &hand2;
    game.hands[3] = &hand3;



	cout << game;
	return 0;
}*/

