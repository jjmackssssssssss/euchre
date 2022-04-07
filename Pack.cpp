#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"

using namespace std;

Pack::Pack() {
    next = 0;
    int counter = 0;
    for( int i = 0; i < NUM_SUITS; ++i) {
        for( int j = 7; j < NUM_RANKS; ++j) {
            cards[counter] = {Card(RANK_NAMES_BY_WEIGHT[j],
            SUIT_NAMES_BY_WEIGHT[i])};
            ++counter;
        }
    }
}

Pack::Pack(istream& pack_input) {
    next = 0;
    int counter = 0;
    string rank;
    string suit;
    string junk;

    for( int i = 0; i < NUM_SUITS; ++i) {
        for( int j = 7; j < NUM_RANKS; ++j) {
            pack_input >> rank;
            pack_input >> junk;
            pack_input >> suit;
            cards[counter] = Card(rank, suit);
            ++counter;
        }
    }
}

Card Pack::deal_one() {
    assert(next < PACK_SIZE);
    ++next;
    return cards[next-1];
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    for(int i = 0; i < 7; ++i) {
        array<Card, PACK_SIZE> tempCards = cards;
        int counter0 = 0;
        int counter1 = 1;
        int tempCounterfh = 0;
        int tempCountersh = PACK_SIZE/2;
        for( int j = 0; j < PACK_SIZE/2 ; ++j) {
            cards[counter1] = tempCards[tempCounterfh];
            cards[counter0] = tempCards[tempCountersh];
            counter0 += 2;
            counter1 += 2;
            ++tempCounterfh;
            ++tempCountersh;
        }
    }
    next = 0;
}

bool Pack::empty() const {
    if(next == PACK_SIZE) {
        return true;
    }
    else {
        return false;
    }
}