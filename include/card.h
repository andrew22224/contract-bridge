#ifndef CARD_H
#define CARD_H

#include <ostream>
#include <string>

using namespace std;

enum Rank {
TWO = 2,
THREE,
FOUR,
FIVE,
SIX,
SEVEN,
EIGHT,
NINE,
TEN,
JACK,
QUEEN,
KING,
ACE,
};

enum Suit {
CLUBS,
DIAMONDS,
HEARTS,
SPADES,
};

/// This class creates card objects with suit and rank variables.
///
class Card {
public:

    /// \brief
    /// Creates a card object with a rank of two and suit of clubs.
    Card();

    /// \brief
    /// Creates a card object and sets rank and suit based on the two input parameters.
    ///
    /// \param rank Rank - a Rank enum value used to assign the card's rank.
    /// \param suit Suit - a Suit enum value used to assign the cards suit.
    Card(Rank rank, Suit suit);

    /// \brief
    /// Creates a card object and sets rank and suit based on the string input.
    ///
    /// \param cardString string - a string used to assign the rank and suit values of the card (eg. "TC" is ten of clubs)
    Card(string cardString);

    /// \brief
    /// Does nothing as no dynamic objects are created by constructor Card();
    ~Card();

    /// \brief
    /// Returns the rank of the current card.
    ///
    /// \return Rank - enum value representing the rank of the current card.
    Rank getRank();

    /// \brief
    /// Returns the suit of the current card.
    ///
    /// \return Suit - enum value representing the suit of the current card.
    Suit getSuit();

    /// \brief
    /// Compares two card pointers and returns whether the first's rank in greater than the second.
    ///
    /// \param cardPtrOne Card* - a pointer to the first card.
    /// \param cardPtrTwo Card* - a pointer to the second card.
    ///
    /// \return bool - returns true if card one's rank value is greater than the second otherwise returns false.
    bool operator()(Card* cardPtrOne, Card* cardPtrTwo);

    /// \brief
    /// Creates an output stream for card class by overloading << operator.
    friend ostream& operator<<(ostream&, Card&);


private:
    Rank cardRank;
    Suit cardSuit;

    /// \brief
    /// Displays the current card as a string
    ///
    /// \return string - returns card as two character string such as "TC".
    string toString();
};

#endif
