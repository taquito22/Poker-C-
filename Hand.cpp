#include "Hand.h"
#include <iostream> 


Hand::Hand()  :  cards(nullptr), size(0), capacity(0)  {}

Hand::Hand(const Hand& other) : capacity(other.size), size(other.size) {
    cards = new Card[capacity];
    for (size_t i = 0; i < size; ++i) {
        cards[i] = other.cards[i];
    }
}


Hand::~Hand(){
    delete[] cards;
}

void Hand::add(Card card) {
    if (size == capacity) {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2; 
        Card* temp = new Card[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            temp[i] = cards[i];
        }
        delete[] cards;
        cards = temp;
        capacity = newCapacity;
    }

    size_t insertIndex = 0;
    while (insertIndex < size && cards[insertIndex] > card) {
        insertIndex++;
    }

    for (size_t i = size; i > insertIndex; --i) {
        cards[i] = cards[i - 1];
    }

    cards[insertIndex] = card;
    size++;
}


void Hand::clear() {
    delete[] cards;
    cards = nullptr;
    capacity = size = 0;
}


size_t Hand::count() const {
    return size;
}


Card Hand::get(size_t index) const {
    return cards[index];
}

void Hand::print() const {
    for (size_t i = 0; i < size; ++i) {
        cards[i].print();
        if (i != size - 1) {
            std::cout << " ";
        }
    }
}

void Hand::resize(size_t newCapacity) {
    Card* temp = new Card[newCapacity];
    for (size_t i = 0; i < size; ++i) {
        temp[i] = cards[i];
    }
    delete[] cards;
    cards = temp;
    capacity = newCapacity;
}

Hand* make_hand() {
    return new Hand();
}

