#include "hand.h"

/// This class sets up a player hand by storing collections of cards for the four different suits.
///

/// \brief
/// Adds the first nodes of the four suit lists to an suit cards array.
Hand::Hand() {

    // Adds first node of each suit list to suitCards array
    this->suitCards[CLUBS] = &this->c_header;
    this->suitCards[DIAMONDS] = &this->d_header;
    this->suitCards[HEARTS] = &this->h_header;
    this->suitCards[SPADES] = &this->s_header;
}

/// \brief
/// Iterates through the suit cards array starting with each suit's first node and deletes all nodes that
/// connect to form that suit list before moving to the next suit.
Hand::~Hand() {
    for (int i = 0; i < NUMSUITS; i++) {
        iteratorNode = *suitCards[i];
        cardNode* temp;

        // Iterate through nodes until last node
        while(iteratorNode != NULL) {

            // Delete nodes
            temp = iteratorNode->next;
            delete(iteratorNode);
            iteratorNode = temp;
        }
    }
}

/// \brief
/// Clears the lists for each suit in the hand by returning the header node for each suit to NULL.
/// Also resets the strength of the hand as all cards have been removed.
void Hand::clear() {

    //Set header nodes to null so that new suit lists can be created
    c_header = NULL;
    d_header = NULL;
    h_header = NULL;
    s_header = NULL;
    handStrength = 0;
}

/// \brief
/// Adds a card node to the correct suit list depening on card pointer given as input parameter
/// (eg. clubs card adds a node to the clubs list).
///
/// \param cardToAdd Card* - used to determine which suit list the card node should be added to.
void Hand::addCard(Card* cardToAdd) {

    // Create node with card pointer as its data variable
    node = new cardNode;
    node->data = cardToAdd;

    cardNode* header;

    switch(cardToAdd->getSuit()) {
        case CLUBS:
            insertCard(c_header, node);
            header = c_header;
            break;
        case SPADES:
            insertCard(s_header, node);
            header = s_header;
            break;
        case HEARTS:
            insertCard(h_header, node);
            header = h_header;
            break;
        case DIAMONDS:
            insertCard(d_header, node);
            header = d_header;
            break;
    }

    // Calculating high card points and length points
    checkForHighCard(cardToAdd);
    if (suitSize(header) > 4) {
        handStrength++;
    }
}

/// \brief
/// Decides what bid for the player to make depending on their hand strength and shape values.
///
/// \return string - the bid that the player should make.
string Hand::makeBid() {
    int longestNum = calculateLongestSuit();
    bool handBalanced = calculateShape();

    if (!handBalanced) {
        if (handStrength <= 12) {
            switch(longestNum) {
                case 6:

                    // Bid highest suit if there are two suits of size 6
                    if (longestSuit.size() == 2) {
                        bid = "2" + suitName(longestSuit.back());
                        break;
                    }

                    // Passes if clubs suit is of size 6
                    if (longestSuit.front() == 0) {
                        bid = "PASS";
                        break;
                    }

                    bid = "2" + suitName(longestSuit.front());
                    break;
                case 7:
                    bid = "3" + suitName(longestSuit.front());
                    break;
                case 8:
                    bid = "4" + suitName(longestSuit.front());
                    break;
                default:
                    bid = "PASS";
                    break;
            }
        }

        else if (handStrength <= 21) {

            // Bid the longest suit
            if (longestSuit.size() == 1) {
                bid = "1" + suitName(longestSuit.front());
            }

            // Bids highest suit if two suits have a size of four or lowest
            // suit if two suits have a size of 5 or more.
            else {
                if (longestNum == 4) {
                    bid = "1" + suitName(longestSuit.front());
                }
                else {
                    bid = "1" + suitName(longestSuit.back());
                }
            }
        }
        else {
            bid = "2C";
        }
    }

    else {
        if (handStrength <= 12) {
            bid = "PASS";
        }
        else if (handStrength <= 14) {
            bidMinorSuit();
        }
        else if (handStrength <= 17) {
            bid = "1NT";
        }
        else if (handStrength <= 19) {
            bidMinorSuit();
        }
        else if (handStrength <= 21) {
            bid = "2NT";
        }
        else {
            bid = "2C";
        }
    }
    return bid;
}

/// \brief
/// Creates an output stream for hand class by overloading << operator.
/// This output will return a string representation of the cards within the hand divided into each suit.
ostream& operator << (ostream& out, Hand& hand) {
    out << "Spades\t :";
    hand.displaySuit(out, hand.s_header);
    out << endl << "Hearts\t :";
    hand.displaySuit(out, hand.h_header);
    out << endl << "Diamonds :";
    hand.displaySuit(out, hand.d_header);
    out << endl << "Clubs\t :";
    hand.displaySuit(out, hand.c_header);

    return out;
}

/// \brief
/// Checks if card has a high rank and adds points to hand strength
/// corresponding to the rank.
///
/// \param cardToAdd Card* - card who's rank will be evaluated.
void Hand::checkForHighCard(Card* cardToAdd) {
    switch(cardToAdd->getRank()) {
        case ACE:
            handStrength += 4;
            break;
        case KING:
            handStrength += 3;
            break;
        case QUEEN:
            handStrength += 2;
            break;
        case JACK:
            handStrength++;
            break;
    }
}

/// \brief
/// Calculates the shape of the hand (balanced or unbalanced) depending on
/// the number of cards in each different suit.
///
/// \return bool - returns true if balanced and false if not.
bool Hand::calculateShape() {
    bool handBalanced = true;
    int numTwoSuits = 0;

    for (int i = 0; i < NUMSUITS; i++) {

        // Set header to the next suit's header each time loop is entered
        cardNode* header = *this->suitCards[(Suit) i];

        // Check that the suit is not less than two or greate than four in size
        if (suitSize(header) < 2 || suitSize(header) > 4) {
            handBalanced = false;
            break;
        }

        if (suitSize(header) == 2) {
            numTwoSuits++;

            // Checks that only zero or one suits are of size two
            if (numTwoSuits > 1) {
                handBalanced = false;
            }
        }
    }
    return handBalanced;
}

/// \brief
/// Determines how many suits are the longest and how many cards they have.
///
/// \return int - returns number of cards in the longest suit/s.
int Hand::calculateLongestSuit() {
    int longestNum = 0;
    for (int i = 0; i < NUMSUITS; i++) {

        // Set header to the next suit's header each time loop is entered
        cardNode* header = *this->suitCards[(Suit) i];

        // Does the current suit have a greater size than the current longest
        if (longestNum < suitSize(header)) {
            longestNum = suitSize(header);

            // Clears previous longest suit and adds new one
            longestSuit.clear();
            longestSuit.push_back((Suit) i);
        }

        // if the current suit has the same size as the current longest
        else if (longestNum == suitSize(header)) {

            // Add to the list of longest suits
            longestSuit.push_back((Suit) i);
        }
    }
    return longestNum;
}

/// \brief
/// Determines the number of cards in a suit by counting the nodes it a suit list.
///
/// \param suit_headerNode cardNode* - first node of the suit list to be calculated.
///
/// \return int - returns number of cards in the suit.
int Hand::suitSize(cardNode* suit_headerNode) {
    int num = 0;
    iteratorNode = suit_headerNode;
    while(iteratorNode != NULL) {
        num++;
        iteratorNode = iteratorNode->next;
    }
    return num;
}

/// \brief
/// Creates a string representation of the cards in given suit to be passed to the hand class output stream.
///
/// \param out ostream& - output stream to receive the output produced by this method.
/// \param suit_headerNode cardNode* - the first node of the suit to be displayed a string.
void Hand::displaySuit(ostream& out, cardNode* suit_headerNode) {
    iteratorNode = suit_headerNode;
    Card* cardPtr;
    while(iteratorNode != NULL) {
        out << " ";
        cardPtr = iteratorNode->data;
        out << *cardPtr;
        iteratorNode = iteratorNode->next;
    }
}

/// \brief
/// Inserts a card node pointer to a card to the correct suit list in the correct place.
///
/// \param suit_headerNode cardNode*& - first node of the suit list where card is to be added.
/// \param node cardNode* - node pointing to card to be added to list.
void Hand::insertCard(cardNode*& suit_headerNode, cardNode* node) {
    Card greaterThan;

    // Check if suit list is not empty
    if (suit_headerNode == NULL) {
        suit_headerNode = node;
        node->next = NULL;
    }

    // Check if the new node is greater than the current first node
    else if (greaterThan(node->data, suit_headerNode->data)) {
        node->next = suit_headerNode;

        // Set new node as new first node
        suit_headerNode = node;
    }

    else {
        for (cardNode* temp = suit_headerNode; temp != NULL; temp = temp->next) {

            // End of list has being reached
            if (temp->next == NULL) {
                temp->next = node;
                node->next = NULL;
            }

            // Current node is greater than next node
            else if (greaterThan(node->data, temp->next->data)) {
                node->next = temp->next;
                temp->next = node;
                break;
            }
        }
    }
}

/// \brief
/// Returns a string representation of the suit value (eg. 0 is Clubs, 1 is Diamonds...).
///
/// \param suitValue int - value corrosponding to SUIT enum values representing a suit.
///
/// \return string - returns suit name as string that the suit value corresponds to.
string Hand::suitName(int suitValue) {
    switch(suitValue) {
        case 0:
            return "C";
            break;
        case 1:
            return "D";
            break;
        case 2:
            return "H";
            break;
        case 3:
            return "S";
            break;
    }
}

/// \brief
/// Bids longest of minor suits (diamonds or clubs). However if suits are both length of four bids
/// bids diamonds and if length is three bids clubs.
void Hand::bidMinorSuit() {
    if (suitSize(d_header) == suitSize(c_header)) {
        if (suitSize(d_header) == 4) {
            bid = "1D";
        }
        else {
            bid = "1C";
        }
    }
    else if (suitSize(d_header) > suitSize(c_header)) {
        bid = "1D";
    }
    else {
        bid = "1C";
    }
}
