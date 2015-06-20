#include "deck.h"
#include "random.h"

/// This class creates an array representing a deck that contains pointers to cards.
///

/// \brief
/// Creates a array of 52 pointers to card objects representing a standard deck of cards.
Deck::Deck() {
    int cardAdded = 0;

    this->cards = new Card*[NUMCARDS];

    // Fills cards array with all cards in order
    for (Suit cardSuit = CLUBS; cardSuit <= SPADES; cardSuit = (Suit) (int) (cardSuit + 1)) {
            for (Rank cardRank = TWO; cardRank <= ACE; cardRank = (Rank) (int) (cardRank + 1)) {
                this->cards[cardAdded] = new Card((Rank) (cardRank), (Suit) (cardSuit));
                cardAdded++;
            }
    }
}

/// \brief
/// Iterates through the array deleting each card pointer and then deletes the array itself.
Deck::~Deck() {
    Card* cardPtr;
    int i = -1;

    // iterates through cards array to delete each card pointer
    while (NUMCARDS > ++i) {
        cardPtr = this->cards[i];
        delete(cardPtr);
    }

    // deletes cards array itself
    delete(this->cards);
}

/// \brief
/// Resets the cards dealt to 0 so that the deck can be re-dealt.
void Deck::reset() {
    cardsDealt = 0;
}

/// \brief
/// Returns the next card in the deck to be dealt by incrementing the cards dealt variable.
///
/// \return Card* - a pointer to the card to be dealt.
Card* Deck::dealNextCard() {
    cardsDealt++;
    return this->cards[cardsDealt - 1];
}

/// \brief
/// Randomly shuffles the card pointers in the deck.
void Deck::shuffle() {
    int minIndex = 0;
    int maxIndex = NUMCARDS - 1;
    Random randomizer;

    // Swaps random pointers
    for (int i = 0; i < NUMSHUFFLESWAPS; i++) {
        int firstIndex = randomizer.randomInteger(minIndex, maxIndex);
        int secondIndex = randomizer.randomInteger(minIndex, maxIndex);
        Card* temp = cards[firstIndex];
        cards[firstIndex] = cards[secondIndex];
        cards[secondIndex] = temp;
    }

}

/// \brief
/// Creates an output stream for deck class by overloading << operator.
/// This output will create a string representation of the deck in its current state, shuffled or not.
ostream& operator<<(ostream& out, Deck& deck) {
    Card* pCard;
    out << "Deck:";

    // Prints each card in cards array
    for (int i = 0; i < NUMCARDS; i++) {
        pCard = deck.dealNextCard();
        out << " ";
        out << *pCard;
	}
	return out;
}

/// \brief
/// Creates 52 cards and adds them to a deck using an input stream.
/// This input stream contains a string representing a card to be created (eg. 2C, 5D).
istream& operator>>(istream& in, Deck& deck) {
    string inputString;

    for (int i = 0; i < NUMCARDS; i++) {

        // Creates card from string in text file
        in >> inputString;
        deck.cards[i] =  new Card(inputString);
    }
    return in;
}


