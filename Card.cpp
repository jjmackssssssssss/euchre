// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <cstring>
#include "Card.h"

using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

Card::Card() {
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

Card::Card(const string &rank_in, const string &suit_in) :rank(rank_in),
suit(suit_in) {}

string Card:: get_rank() const {
    return rank;
}

string Card:: get_suit() const {
    return suit;
}
//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
string Card:: get_suit(const string &trump) const{
    if (rank == RANK_JACK && suit == Suit_next(trump)) {
        return trump;
    }
    else {
        return suit;
    }
}
//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card:: is_face() const {
    if ((rank == RANK_JACK) || (rank == RANK_QUEEN) ||
        (rank == RANK_KING) || (rank == RANK_ACE)) {
        return true;
    }
    else {
        return false;
    }

}
//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit

bool Card:: is_right_bower(const string &trump) const {
    if (rank == Card::RANK_JACK) {
        if (suit == trump) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}
//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card:: is_left_bower(const string &trump) const {
    if (rank == Card::RANK_JACK) {
        if (suit == Suit_next(trump)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card:: is_trump(const string &trump) const {
    if (suit == trump) {
        return true;
    }
    if (is_left_bower(trump)) {
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    int count = 0;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    for(int i= 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            count = i;
        }
    }
    for (int j =0; j < NUM_RANKS; j++) {
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            count1= j;
        }
    }
    for (int k =0; k < NUM_SUITS; k++) {
        if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[k]) {
            count2 = k;
    }
    }
    for (int a=0; a <NUM_SUITS; a++) {
        if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[a]) {
            count3 = a;
        }
    }
    if (count1 > count) {
        return true;
    }
    else if (count1 == count) {
        if (count3 > count2) {
            return true;
        }
    }
    return false;
    
}
//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
        int counter = 0;
        int counter11 = 0;
        int counter22 = 0;
        int counter33 = 0;
        for(int i= 0; i < NUM_RANKS; i++) {
            if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
                counter = i;
            }
        }
        for (int j =0; j < NUM_RANKS; j++) {
            if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
                counter11 = j;
            }
        }
        for (int k =0; k < NUM_SUITS; k++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[k]) {
                counter22 = k;
        }
        }
        for (int a=0; a <NUM_SUITS; a++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[a]) {
                counter33 = a;
            }
        }
        if (counter11 < counter) {
            return true;
        }
        else if (counter11 == counter) {
            if (counter33 < counter22) {
                return true;
            }
        }
        return false;
        
    }

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    int count00 = 0;
    int count11 = 0;
    int count22 = 0;
    int count33 = 0;
    for(int i= 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
                   count00 = i;
               }
           }
    for (int j =0; j < NUM_RANKS; j++) {
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
                   count11 = j;
               }
           }
    for (int k =0; k < NUM_SUITS; k++) {
        if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[k]) {
                   count22 = k;
           }
           }
    for (int a=0; a <NUM_SUITS; a++) {
        if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[a]) {
                   count33 = a;
               }
           }
    if (count11 == count00) {
        if (count22 == count33) {
            return true;
           }
    }
    return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    int counter0 = 0;
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    for(int i= 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            counter0 = i;
        }
    }
    for (int j =0; j < NUM_RANKS; j++) {
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            counter1 = j;
        }
    }
    for (int k =0; k < NUM_SUITS; k++) {
        if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[k]) {
            counter2 = k;
        }
    }
    for (int a=0; a <NUM_SUITS; a++) {
        if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[a]) {
            counter3 = a;
        }
    }
    if (counter1 == counter0) {
        if (counter2 == counter3) {
            return false;
        }
    }
    return true;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
string Suit_next(const string &suit) {
    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    }
    return 0;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
ostream & operator<<(ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
    if(!a.is_trump(trump) && b.is_trump(trump)) {
        if(a.is_left_bower(trump) && !b.is_right_bower(trump)) {
            return false;
        }
        else{
            return true;
        }
    }
    else if (a.is_trump(trump) && !b.is_trump(trump)) {
        if(b.is_left_bower(trump) && !a.is_right_bower(trump)) {
            return true;
        }
        else{
            return false;
        }
    }
    else if (a.is_trump(trump) && b.is_trump(trump)) {
         if ((!a.is_right_bower(trump) && b.is_right_bower(trump))
             || (b.is_left_bower(trump) && a.is_trump(trump))
             || (b.is_right_bower(trump) && a.is_left_bower(trump))) {
             return true;
         }
         else if ((a.is_right_bower(trump) && !b.is_right_bower(trump)) ||
                    (a.is_right_bower(trump) && !b.is_right_bower(trump))
                  || (a.is_left_bower(trump) && b.is_trump(trump))
                  || (a.is_right_bower(trump) && b.is_left_bower(trump)))  {
             return false;
         }
         else if (a < b) {
             return true;
         }
         else {
             return false;
         }
    }
   else if (!a.is_trump(trump) && !b.is_trump(trump)) {
        if (a < b) {
            return true;
        }
        else {
            return false;
        }
    }
   else {
       return 1;
   }
}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const string &trump){
    if (!a.is_trump(trump) && b.is_trump(trump)) {
        if(a.is_left_bower(trump) && !b.is_right_bower(trump)) {
            return false;
        }
        return true;
    }
    else if (a.is_trump(trump) && !b.is_trump(trump)) {
        if(b.is_left_bower(trump) && !a.is_right_bower(trump)) {
            return true;
        }
         return false;
    }
    else if (a.is_trump(trump) && b.is_trump(trump)) {
        if (!a.is_right_bower(trump) && b.is_right_bower(trump)) {
            return true;
            }
        else if (a.is_right_bower(trump) && !b.is_right_bower(trump)) {
            return false;}
        else if(a.is_left_bower(trump) && !b.is_right_bower(trump)) {
            return false;}
        else if(!a.is_right_bower(trump) && b.is_left_bower(trump)) {
            return true;}
        else if (a < b) {
            return true;}
        else {
            return false;}}
    else {
        if (led_card.get_suit() != a.get_suit() &&
            led_card.get_suit() == b.get_suit()) { 
            return true;
         }
        else if (led_card.get_suit() == a.get_suit() &&
                 led_card.get_suit() != b.get_suit()) {
            return false;
        }
        else if (a < b) {
            return true;
        }
        else {
            return false;
        }
    }
}

                







