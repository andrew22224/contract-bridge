#include "card.h"

/// This class creates card objects with suit and rank variables.
///

/// \brief
/// Creates a card object with a rank of two and suit of clubs.
Card::Card() {
    this->cardRank = TWO;
    this->cardSuit = CLUBS;
}

/// \brief
/// Creates a card object and sets rank and suit based on the two input parameters.
///
/// \param rank Rank - a Rank enum value used to assign the card's rank.
/// \param suit Suit - a Suit enum value used to assign the cards suit.
Card::Card(Rank rank, Suit suit) {
    this->cardRank = rank;
    this->cardSuit = suit;
}

/// \brief
/// Creates a card object and sets rank and suit based on the string input.
///
/// \param cardString string - a string used to assign the rank and suit values of the card (eg. "TC" is ten of clubs)
Card::Card(string cardString) {
    char rankChar = cardString[0];
    char suitChar = cardString[1];

    switch(rankChar) {
    case 'T':
        this->cardRank = TEN;
        break;
    case 'J':
        this->cardRank = JACK;
        break;
    case 'Q':
        this->cardRank = QUEEN;
        break;
    case 'K':
        this->cardRank = KING;
        break;
    case 'A':
        this->cardRank = ACE;
        break;
    default:
        this->cardRank = (Rank)((int)rankChar - '0');
        break;
    }

    switch(suitChar) {
        case 'C':
            this->cardSuit = CLUBS;
            break;
        case 'D':
            this->cardSuit = DIAMONDS;
            break;
        case 'H':
            this->cardSuit = HEARTS;
            break;
        case 'S':
            this->cardSuit = SPADES;
            break;
    }
}

/// \brief
/// Does nothing as no dynamic objects are created by constructor Card();
Card::~Card() {}

/// \brief
/// Returns the rank of the current card.
///
/// \return Rank - enum value representing the rank of the current card.
Rank Card::getRank() {
    return this->cardRank;
}

/// \brief
/// Returns the suit of the current card.
///
/// \return Suit - enum value representing the suit of the current card.
Suit Card::getSuit() {
    return this->cardSuit;
}

/// \brief
/// Compares two card pointers and returns whether the first's rank in greater than the second.
///
/// \param cardPtrOne Card* - a pointer to the first card.
/// \param cardPtrTwo Card* - a pointer to the second card.
///
/// \return bool - returns true if card one's rank value is greater than the second otherwise returns false.
bool Card::operator()(Card* cardPtrOne, Card* cardPtrTwo) {
   return cardPtrOne->getRank() > cardPtrTwo->getRank();
}

/// \brief
/// Creates an output stream for card class by overloading << operator.
/// This output will return the card represented by a string.
ostream& operator<<(ostream& out, Card& card) {
    out << card.toString();
    return out;
}

/// \brief
/// Displays the current card as a string
///
/// \return string - returns card as two character string such as "TC".
string Card::toString() {
    string cardName = "";

    if ((int)this->cardRank >= (int)TWO && (int)this->cardRank <= (int)NINE) {
        cardName += (int)this->cardRank + '0';
    }
    else {
        switch(this->cardRank) {
            case TEN: cardName += "T"; break;
            case JACK: cardName += "J"; break;
            case QUEEN: cardName += "Q"; break;
            case KING: cardName += "K"; break;
            case ACE: cardName += "A"; break;
        }
    }

    switch(this->cardSuit) {
            case CLUBS: cardName += "C"; break;
            case SPADES: cardName += "S"; break;
            case DIAMONDS: cardName += "D"; break;
            case HEARTS: cardName += "H"; break;
    }

    return cardName;
}
