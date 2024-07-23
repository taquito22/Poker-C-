#ifndef HAND_H
#define HAND_H

#include "Card.h"

class Hand {
private:
    Card* cards; 
    size_t capacity; 
    size_t size; 

    void resize(size_t newCapacity);

public:
    Hand();
    Hand(const Hand& other);
    ~Hand();

    void add(Card card);
    void clear();
    size_t count() const;
    Card get(size_t index) const;
    void print() const;
    Hand* best_hand(const Hand& cards);
     bool isFullHouse(const Hand& hand);
};

Hand* make_hand();

#endif 