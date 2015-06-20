#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "deck.h"
#include "hand.h"

using namespace std;

enum Position {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

const int NUMPOSITIONS = 4;

/// This class creates a game by creating a deck and providing players with hands of cards.
///
class Game
{
    public:
        /// \brief
        /// Starts a game by creating an array to hold the four player hands and decided on dealer.
        Game();

        /// \brief
        /// Deletes the pointers to hand objects contained within the array before deleting the array itself.
        ~Game();

        /// \brief
        /// Sets up the game either from file or by shuffling a created deck.
        ///
        /// \param fromFile bool - true or false value indicating if a text file is being used to create a game.
        void setup(bool fromFile);

        /// \brief
        /// Deals the cards to the four players by iterating through deck and adding cards to players.
        void deal();

        /// \brief
        /// Calls make bid function, from Hand class, for each player starting with dealer untill someone
        /// makes a bid other than pass.
        void auction();

        /// \brief
        /// Sets dealer position to the player clockwise of current dealer.
        void nextDealer();

        /// \brief
        /// Creates an output stream for game class by overloading << operator.
        /// This output will return a string represenation of the game including the player's
        /// names and the cards they have in their hands divided into the various suits.
        friend ostream& operator<<(ostream& out, Game& game);

        /// \brief
        /// Calls upon the deck input stream to read the cards from the text file provided.
        friend istream& operator>>(istream& in, Game& game);

    private:
        Position dealer;
        Deck deck;
        string openingBid;
        Hand* hands[NUMPOSITIONS];

        /// \brief
        /// Returns string indicating the name of the position value.
        ///
        /// \param positionValue int - a value representing a player position (eg. 0 is North, 1 is East...).
        ///
        /// \return string - A string containing the name of the position.
        string PositionName(int positionValue);

};

#endif // GAME_H
