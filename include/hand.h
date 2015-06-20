#ifndef HAND_H
#define HAND_H

#include <list>
#include "deck.h"
#include "card.h"

using namespace std;

const int NUMSUITS = 4;

/// This class sets up a player hand by storing collections of cards for the four different suits.
///
class Hand
{
    public:

        /// \brief
        /// Adds the first nodes of the four suit lists to an suit cards array.
        Hand();

        /// \brief
        /// Iterates through the suit cards array starting with each suit's first node and deletes all nodes that
        /// connect to form that suit list before moving to the next suit.
        ~Hand();

        /// \brief
        /// Clears the lists for each suit in the hand by returning the header node for each suit to NULL.
        /// Also resets the strength of the hand as all cards have been removed.
        void clear();

        /// \brief
        /// Adds a card node to the correct suit list depening on card pointer given as input parameter
        /// (eg. clubs card adds a node to the clubs list).
        ///
        /// \param cardToAdd Card* - used to determine which suit list the card node should be added to.
        void addCard(Card* cardToAdd);

        /// \brief
        /// Decides what bid for the player to make depending on their hand strength and shape values.
        ///
        /// \return string - the bid that the player should make.
        string makeBid();

        /// \brief
        /// Creates an output stream for hand class by overloading << operator.
        /// This output will return a string representation of the cards within the hand divided into each suit.
        friend ostream& operator << (ostream& out, Hand& hand);

    private:
        struct cardNode { Card* data; cardNode* next; };
        cardNode* node;
        cardNode* c_header = NULL;
        cardNode* s_header = NULL;
        cardNode* h_header = NULL;
        cardNode* d_header = NULL;
        cardNode* iteratorNode;
        cardNode** suitCards[NUMSUITS];
        string bid;
        list<Suit> longestSuit;
        int handStrength = 0;

        /// \brief
        /// Checks if card has a high rank and adds points to hand strength
        /// corresponding to the rank.
        ///
        /// \param cardToAdd Card* - card who's rank will be evaluated.
        void checkForHighCard(Card* cardToAdd);

        /// \brief
        /// Calculates the shape of the hand (balanced or unbalanced) depending on
        /// the number of cards in each different suit.
        ///
        /// \return bool - returns true if balanced and false if not.
        bool calculateShape();

        /// \brief
        /// Determines how many suits are the longest and how many cards they have.
        ///
        /// \return int - returns number of cards in the longest suit/s.
        int calculateLongestSuit();

        /// \brief
        /// Determines the number of cards in a suit by counting the nodes it a suit list.
        ///
        /// \param suit_headerNode cardNode* - first node of the suit list to be calculated.
        ///
        /// \return int - returns number of cards in the suit.
        int suitSize(cardNode* suit_headerNode);

        /// \brief
        /// Creates a string representation of the cards in given suit to be passed to the hand class output stream.
        ///
        /// \param out ostream& - output stream to receive the output produced by this method.
        /// \param suit_headerNode cardNode* - the first node of the suit to be displayed a string.
        void displaySuit(ostream& out, cardNode* suit_headerNode);

        /// \brief
        /// Inserts a card node pointer to a card to the correct suit list in the correct place.
        ///
        /// \param suit_headerNode cardNode*& - first node of the suit list where card is to be added.
        /// \param node cardNode* - node pointing to card to be added to list.
        void insertCard(cardNode*& suit_headerNode, cardNode* node);

        /// \brief
        /// Returns a string representation of the suit value (eg. 0 is Clubs, 1 is Diamonds...).
        ///
        /// \param suitValue int - value corrosponding to SUIT enum values representing a suit.
        ///
        /// \return string - returns suit name as string that the suit value corresponds to.
        string suitName(int suitValue);

        /// \brief
        /// Bids longest of minor suits (diamonds or clubs). However if suits are both length of four bids
        /// bids diamonds and if length is three bids clubs.
        void bidMinorSuit();
};

#endif // HAND_H
