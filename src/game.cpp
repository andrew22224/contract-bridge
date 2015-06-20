#include "game.h"

/// This class creates a game by creating a deck and providing players with hands of cards.
///

/// \brief
/// Starts a game by creating an array to hold the four player hands and decided on dealer.
Game::Game()
{
    for (int i = 0; i < NUMPOSITIONS; i++) {
        this->hands[i] = new Hand();
    }
    this->dealer = NORTH;
}

/// \brief
/// Deletes the pointers to hand objects contained within the array before deleting the array itself.
Game::~Game()
{

    // Deletes each hand object for all players
    for (int i = 0; i < NUMPOSITIONS; i++) {
        delete(hands[i]);
    }

    // Deletes hands array itself
    delete(hands);
}

/// \brief
/// Sets up the game either from file or by shuffling a created deck.
///
/// \param fromFile bool - true or false value indicating if a text file is being used to create a game.
void Game::setup(bool fromFile) {

    // Shuffle if deck is not been created from text file.
    if (!fromFile) {
        deck.shuffle();
    }

    deck.reset();

    // Clear hand objects from previous games
    for (int i = 0; i < NUMPOSITIONS; i++) {
        hands[i]->clear();
    }
}

/// \brief
/// Deals the cards to the four players by iterating through deck and adding cards to players.
void Game::deal() {

    // Finds the player to dealers left to receive first card
    int first = ((int) dealer + 1) % NUMPOSITIONS;

    for (int i = 0; i < NUMCARDS; i++) {
        this->hands[(i + first) % NUMPOSITIONS]->addCard(deck.dealNextCard());
    }
}

/// \brief
/// Calls make bid function, from Hand class, for each player starting with dealer untill someone
/// makes a bid other than pass.
void Game::auction() {

    // Iterate through players and call make bid
    for (int i = (int) dealer; i < (NUMPOSITIONS + (int) dealer); i++) {
        string bid = hands[i % NUMPOSITIONS]->makeBid();
        if (bid != "PASS") {
            openingBid = "Opening bid is " + bid + " made by " + PositionName(i % NUMPOSITIONS);

            // Break out of loop as bid has being made
            return;
        }
    }
    openingBid = "All hands passed";
}

/// \brief
/// Sets dealer position to the player clockwise of current dealer.
void Game::nextDealer() {
    dealer = (Position) (((int) dealer + 1) % NUMPOSITIONS);
}

/// \brief
/// Creates an output stream for game class by overloading << operator.
/// This output will return a string represenation of the game including the player's
/// names and the cards they have in their hands divided into the various suits.
ostream& operator<<(ostream& out, Game& game) {
    for (int i = 0; i < NUMPOSITIONS; i++) {
        out << game.PositionName(i) << endl;
        out << *game.hands[i] << endl;
        out << endl;
    }
    out << game.openingBid << endl;
    return out;
}

/// \brief
/// Calls upon the deck input stream to read the cards from the text file provided.
istream& operator>>(istream& in, Game& game) {
    in >> game.deck;
    return in;
}

/// \brief
/// Returns string indicating the name of the position value.
///
/// \param positionValue int - a value representing a player position (eg. 0 is North, 1 is East...).
///
/// \return string - A string containing the name of the position.
string Game::PositionName(int positionValue) {
    string positionName;
    switch(positionValue) {
        case 0:
            return positionName = "NORTH";
        case 1:
            return positionName = "EAST";
        case 2:
            return positionName = "SOUTH";
        case 3:
            return positionName = "WEST";
    }
}



