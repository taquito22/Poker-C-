#include "ListCard.h"

// Default constructor
Hand::Hand() : first(nullptr) {}

// Copy constructor
Hand::Hand(const Hand& other) : first(nullptr) {
    const Node* temp = other.head();
    while (temp != nullptr) {
        add(temp->card);
        temp = temp->next;
    }
}

// Destructor
Hand::~Hand() {
    clear();
}

// Add a card to the hand
void Hand::add(Card card) {
    Node* newNode = new Node(card, nullptr);
    if (first == nullptr || card > first->card) {
        newNode->next = first;
        first = newNode;
    } else {
        Node* current = first;
        while (current->next != nullptr && current->next->card > card) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Remove all cards from the hand
void Hand::clear() {
    while (first != nullptr) {
        Node* temp = first;
        first = first->next;
        delete temp;
    }
}

// Return the number of cards in the hand
size_t Hand::count() const {
    size_t count = 0;
    const Node* current = first;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Return the card at the given index
Card Hand::get(size_t index) const {
    const Node* current = first;
    size_t currentIndex = 0;
    while (current != nullptr && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }
    if (current != nullptr) {
        return current->card;
    } else {
        // You may choose to handle index out of bounds differently (throw exception, return default card, etc.)
        return Card();
    }
}

// Return a pointer to the first node in the hand
const Node* Hand::head() const {
    return first;
}

// Print the cards in the hand
void Hand::print() const {
    const Node* current = first;
    while (current != nullptr) {
        current->card.print();
        std::cout << ' ';
        current = current->next;
    }
}