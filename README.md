Poker in C++
Overview
I wanted to play poker in C++, so I decided to code it from scratch.
This project simulates a deck of cards, a hand, and the logic to figure out the best possible poker hand from whatever cards you have.
No fancy libraries here — everything is built using plain C++ and raw arrays.

Features
Custom Hand class
Stores cards in sorted order (highest card first)
Dynamically resizes with heap allocation
Add, clear, count, and print cards
Poker hand evaluator
Detects all major hands:
High Card
Pair
Two Pair
Three of a Kind
Straight
Flush
Full House
Four of a Kind
Straight Flush
Chooses the highest-ranking possible hand from the cards
Standard 52-card deck support (no jokers, no duplicates)
How It Works
Create and populate a Hand with cards.
Pass it to the best_hand() function.
The function returns a new Hand with only the cards that form your best hand.
Print it to see your result.
Example (simplified):
Hand* myHand = make_hand();
myHand->add(Card(ACE, SPADES));
myHand->add(Card(KING, SPADES));
// ... add more cards

Hand* result = best_hand(*myHand);
result->print();

Why I Built This
Mostly because I thought it would be fun to:
Write my own dynamic array class without std::vector
Practice clean header/source separation in C++
Implement poker hand logic from scratch
