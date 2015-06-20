#ifndef DECK_H
#define DECK_H

#include <iostream>
#include "card.h"

using namespace std;

const int NUMCARDS = 52;
const int NUMSHUFFLESWAPS = 1000;

/// This class creates an array representing a deck that contains pointers to cards.
///
class Deck {
public:

    /// \brief
    /// Creates a array of 52 pointers to card objects representing a standard deck of cards.
    Deck();

    /// \brief
    /// Iterates through the array deleting each card pointer and then deletes the array itself.
    ~Deck();

    /// \brief
    /// Resets the cards dealt to 0 so that the deck can be re-dealt.
    void reset();

    /// \brief
    /// Returns the next card in the deck to be dealt by incrementing the cards dealt variable.
    ///
    /// \return Card* - a pointer to the card to be dealt.
    Card* dealNextCard();

    /// \brief
    /// Randomly shuffles the card pointers in the deck.
    void shuffle();

    /// \brief
    /// Creates an output stream for deck class by overloading << operator.
    /// This output will create a string representation of the deck in its current state, shuffled or not.
    friend ostream& operator<<(ostream& out, Deck& deck);

    /// \brief
    /// Creates 52 cards and adds them to a deck using an input stream.
    /// This input stream contains a string representing a card to be created (eg. 2C, 5D).
    friend istream& operator>>(istream& in, Deck& deck);

private:
    Card **cards;
    int cardsDealt = 0;
};

#endif
