#include "Hand.h"
#include "Card.h"

bool has_pair(const Hand& hand) {
    for (size_t i = 0; i < hand.count(); ++i) {
        for (size_t j = i + 1; j < hand.count(); ++j) {
            if (hand.get(i).rank == hand.get(j).rank) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if a hand contains a pair
bool has_two_pair(const Hand& cards) {
    bool firstPairFound = false;
    Rank firstPairRank;
if (cards.count() <= 2) {
        return false;
    }
    for (size_t i = 0; i < cards.count() - 1; ++i) {
        if (cards.get(i).rank == cards.get(i + 1).rank) {
            firstPairFound = true;
            firstPairRank = cards.get(i).rank;
            break;
        }
    }

    if (firstPairFound) {
        for (size_t i = 0; i < cards.count() - 1; ++i) {
            if (cards.get(i).rank != firstPairRank && cards.get(i).rank == cards.get(i + 1).rank) {
                return true; 
            }
        }
    }

    return false; 
}

// Function to check if a hand contains three of a kind
bool has_three_of_a_kind(const Hand& cards) {

    if (cards.count() < 2) {
        return false;
    }

    for (size_t i = 0; i < cards.count() - 2; ++i) {
        if (cards.get(i).rank == cards.get(i + 1).rank &&
            cards.get(i).rank == cards.get(i + 2).rank) {
            return true;
        }
    }
    return false;
}

// Function to check if a hand contains a straight
bool has_straight(const Hand& cards) {
    if (cards.count() < 5) {
        return false;
    }

    // Ace addition
    Hand groupedByRank[14];
    for (size_t i = 0; i < cards.count(); ++i) {
        int rankIndex = cards.get(i).rank - 1;
        if (cards.get(i).rank == 14) {
            groupedByRank[0].add(cards.get(i));
        }
        groupedByRank[rankIndex].add(cards.get(i));
    }

    // Check straight
    size_t currentStraightLength = 0;
    for (int rank = 13; rank >= 0; --rank) {
        if (groupedByRank[rank].count() > 0) {
            ++currentStraightLength;
            if (currentStraightLength == 5) {
                return true; // Straight found, return true
            }
        } else {
            currentStraightLength = 0;
        }
    }

    return false; // Straight not found, return false
}

// Function to check if a hand contains a flush
bool has_flush(const Hand& cards) {

    int suitCount[4] = {0};

    for (size_t i = 0; i < cards.count(); ++i) {
        Suit currentSuit = cards.get(i).suit;
        suitCount[currentSuit]++;
    }

    for (int count : suitCount) {
        if (count >= 5) {
            return true; 
        }
    }

    return false; 
}

bool has_full_house(const Hand& cards) {
    if (cards.count() < 5) {
        return false;
    }

    Rank threeRank = Rank::TWO;
    bool tripletFound = false;
    for (size_t i = 0; i < cards.count() - 2; ++i) {
        if (cards.get(i).rank == cards.get(i + 1).rank &&
            cards.get(i).rank == cards.get(i + 2).rank) {
            threeRank = cards.get(i).rank;
            tripletFound = true;
            break;
        }
    }

    if (!tripletFound) {
        return false; 
    }

    bool pairFound = false;
    for (size_t i = 0; i < cards.count() - 1; ++i) {
        if (cards.get(i).rank != threeRank &&
            cards.get(i).rank == cards.get(i + 1).rank) {
            pairFound = true;
            break;
        }
    }

    return pairFound;
}

// Function to check if a hand contains four of a kind
bool has_four_of_a_kind(const Hand& cards) {
    if (cards.count() <= 2) {
        return false;
    }
    for (size_t i = 0; i < cards.count() - 3; ++i) {

        if (cards.get(i).rank == cards.get(i + 1).rank &&
            cards.get(i).rank == cards.get(i + 2).rank &&
            cards.get(i).rank == cards.get(i + 3).rank) {
            return true;
        }
    }
    return false;
}

// Function to check if a hand contains a straight flush
bool has_straight_flush(const Hand& cards) {
    // Check if the hand has at least 5 cards
    if (cards.count() < 5) {
        return false;
    }

    for (size_t suit = 0; suit <= 3; ++suit){
        size_t s_Count[15] ={};

        for(size_t i = 0; i < cards.count(); ++i){
            if(cards.get(i).suit == static_cast<Suit>(suit)){
                s_Count[cards.get(i).rank]++;
            }
        }

        for(int rank = 14; rank >= 5; --rank){
            bool is_Consec = true;
            for(int offset = 0; offset < 5; ++offset){
                if(s_Count[rank - offset] < 1){
                    is_Consec = false;
                    break;
                }
            }
            if(is_Consec){
                return true;
            }
        }


        if(s_Count[14] >= 1 && s_Count[2] >= 1 && s_Count[3] >= 1 && s_Count[4] >= 1 && s_Count[5] >= 1){
             return true;
         }
    }
    return false;
}



Hand* best_hand(const Hand& cards) {
    Hand* bestHand = make_hand();

if (cards.count() == 0) {
        return bestHand;
}
else if(has_straight_flush(cards)){
    //straight flush addition 


  int suitCount[4] = {0};
    size_t flushEndIndex[4] = {0}; // Tracks the ending index of each flush suit

    for (size_t i = 0; i < cards.count(); ++i) {
        Suit currentSuit = cards.get(i).suit;
        suitCount[currentSuit]++;
        flushEndIndex[currentSuit] = i; 
    }

    Suit flushSuit = Suit::SPADES;
    size_t earliestFlushEndIndex = cards.count(); 
    for (int i = 0; i < 4; ++i) {
        if (suitCount[i] >= 5 && flushEndIndex[i] < earliestFlushEndIndex) {
            flushSuit = static_cast<Suit>(i);
            earliestFlushEndIndex = flushEndIndex[i]; 
        }
    }



Hand groupedByRank[14];
    for (size_t i = 0; i < cards.count(); ++i) {
        int rankIndex = cards.get(i).rank - 1;
        if(cards.get(i).rank == 14){
            groupedByRank[0].add(cards.get(i));
        }
        groupedByRank[rankIndex].add(cards.get(i));
    }

    // check straight
    size_t currentStraightLength = 0;
    for (int rank = 13; rank >= 0; --rank) { 
        if (groupedByRank[rank].count() > 0) {
            ++currentStraightLength;
            if (currentStraightLength == 5) {
                for (int i = rank; i <= rank + 4; ++i) { 
                    for (size_t x = 0; x < groupedByRank[i].count(); ++x){
                        if(groupedByRank[i].get(x).suit == flushSuit){
                        bestHand->add(groupedByRank[i].get(x));  
                        }
                    }
                }
                break;
            }
        } else {
            currentStraightLength = 0;
        }
    }

    return bestHand;
}
else if(has_four_of_a_kind(cards)){
    //fourkind addition
    for (size_t i = 0; i < cards.count() - 3; ++i) {
        if (cards.get(i).rank == cards.get(i + 1).rank &&
            cards.get(i).rank == cards.get(i + 2).rank &&
            cards.get(i).rank == cards.get(i + 3).rank) {

            for (size_t j = i; j < i + 4; ++j) {
                bestHand->add(cards.get(j));
            }
            return bestHand;
        }
    }

}
else if(has_full_house(cards)) {
  Rank threeRank = Rank::TWO;
    bool tripletFound = false;
    for (size_t i = 0; i < cards.count() - 2; ++i) {
        if (cards.get(i).rank == cards.get(i + 1).rank &&
            cards.get(i).rank == cards.get(i + 2).rank) {
            threeRank = cards.get(i).rank;
            tripletFound = true;
            break;
        }
    }

    if (!tripletFound) {
        return bestHand; // No triplet found
    }

    bool pairFound = false;
    for (size_t i = 0; i < cards.count() - 1; ++i) {
        if (cards.get(i).rank != threeRank &&
            cards.get(i).rank == cards.get(i + 1).rank) {
            pairFound = true;
            break;
        }
    }

    if (pairFound) {

        for (size_t i = 0; i < cards.count() - 2; ++i) {
            if (cards.get(i).rank == threeRank &&
                cards.get(i + 1).rank == threeRank &&
                cards.get(i + 2).rank == threeRank) {
                bestHand->add(cards.get(i));
                bestHand->add(cards.get(i + 1));
                bestHand->add(cards.get(i + 2));
                break;
            }
        }
        // Add the pair
        for (size_t i = 0; i < cards.count() - 1; ++i) {
            if (cards.get(i).rank != threeRank &&
                cards.get(i).rank == cards.get(i + 1).rank) {
                bestHand->add(cards.get(i));
                bestHand->add(cards.get(i + 1));
                break;
            }
        }
    }
    return bestHand;
}
else if(has_flush(cards)){
    // flush addition
    int suitCount[4] = {0};
    size_t flushEndIndex[4] = {0}; // Tracks the ending index of each flush suit

    for (size_t i = 0; i < cards.count(); ++i) {
        Suit currentSuit = cards.get(i).suit;
        suitCount[currentSuit]++;
        flushEndIndex[currentSuit] = i; 
    }

    Suit flushSuit = Suit::SPADES;
    size_t earliestFlushEndIndex = cards.count(); 
    for (int i = 0; i < 4; ++i) {
        if (suitCount[i] >= 5 && flushEndIndex[i] < earliestFlushEndIndex) {
            flushSuit = static_cast<Suit>(i);
            earliestFlushEndIndex = flushEndIndex[i]; 
        }
    }


    int flushCardsAdded = 0;
    for (size_t i = 0; i < cards.count(); ++i) {
        if (cards.get(i).suit == flushSuit && flushCardsAdded < 5) {
            bestHand->add(cards.get(i));
            flushCardsAdded++;
        }
    }

    return bestHand;
}
else if (has_straight(cards)) {
    // ace addition
    Hand groupedByRank[14];
    for (size_t i = 0; i < cards.count(); ++i) {
        int rankIndex = cards.get(i).rank - 1;
        if(cards.get(i).rank == 14){
            groupedByRank[0].add(cards.get(i));
        }
        groupedByRank[rankIndex].add(cards.get(i));
    }

    // check straight
    size_t currentStraightLength = 0;
    for (int rank = 13; rank >= 0; --rank) { 
        if (groupedByRank[rank].count() > 0) {
            ++currentStraightLength;
            if (currentStraightLength == 5) {
                for (int i = rank; i <= rank + 4; ++i) { 
                        bestHand->add(groupedByRank[i].get(0));
                }
                break;
            }
        } else {
            currentStraightLength = 0;
        }
    }

    return bestHand;
}
else if(has_three_of_a_kind(cards)){
    //three of a kind
     for (size_t i = 0; i < cards.count() - 2; ++i) {
        if (cards.get(i).rank == cards.get(i + 1).rank &&
            cards.get(i).rank == cards.get(i + 2).rank) {

            for (size_t j = i; j < i + 3; ++j) {
                bestHand->add(cards.get(j));
            }
            return bestHand;
        }
    }
}
else if(has_two_pair(cards)){
    //twoopair addition
bool firstPairFound = false;
    Rank firstPairRank;

 for (size_t i = 0; i < cards.count() - 1; ++i) {
        if (cards.get(i).rank == cards.get(i + 1).rank) {
            firstPairFound = true;
            firstPairRank = cards.get(i).rank;
            bestHand->add(cards.get(i));
            bestHand->add(cards.get(i + 1));
            break;
        }
    }

    if (firstPairFound) {

        for (size_t i = 0; i < cards.count() - 1; ++i) {
            if (cards.get(i).rank != firstPairRank && cards.get(i).rank == cards.get(i + 1).rank) {
                bestHand->add(cards.get(i));
                bestHand->add(cards.get(i + 1));
                break; 
            }
        }
    }

    return bestHand;
}
else if (has_pair(cards)) {
        for (size_t i = 0; i < cards.count() - 1; ++i) {
            if (cards.get(i).rank == cards.get(i + 1).rank) {
                bestHand->add(cards.get(i));
                bestHand->add(cards.get(i + 1));
                break;
            }
        }
}
else{
    if(!has_pair(cards)){
    bestHand->add(cards.get(0));
    return bestHand;
    }
}


return bestHand;
}
