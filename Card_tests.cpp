// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}
TEST(test_is_left_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c.is_left_bower(Card::SUIT_CLUBS));
}
TEST(test_is_left_bower2) {
    Card c(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_CLUBS));
}
TEST(test_is_right_bower) {
    Card d(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(d.is_right_bower(Card::SUIT_SPADES));
}
TEST(test_is_right_bower2) {
    Card d(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_FALSE(d.is_right_bower(Card::SUIT_SPADES));
}
TEST(test_is_trump) {
    Card d(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card e(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(d.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(e.is_trump(Card::SUIT_SPADES));
}
TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
}
TEST(test_Card_less_1) {
    Card e = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card f = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(Card_less(e, f, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(e, f, f, Card::SUIT_CLUBS));
    
}

TEST(test_Card_less_2) {
    Card e = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card f = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card g = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(e, f, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(e, g, Card::SUIT_SPADES));
    
}
TEST(test_Card_less_99) {
    Card f = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card g = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card a = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_FALSE(Card_less(f, g, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(f, a, Card::SUIT_CLUBS));
    
}
TEST(test_Card_less_3) {
    Card e = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card f = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card lead = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(e, f, lead, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(e, f, lead, Card::SUIT_SPADES));

}
TEST(test_Card_less_4) {
    Card e = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card f = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card lead = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_FALSE(Card_less(e, f, lead, Card::SUIT_DIAMONDS));

}
TEST(test_Card_less_77) {
    Card e = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card f = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card lead = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_FALSE(Card_less(e, f, lead, Card::SUIT_CLUBS));

}

TEST(test_card_self_comparison) {
    Card three_spades = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
}
TEST(test_card_other_comparison) {
    Card F = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card G = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(F < G);
    ASSERT_FALSE(F > G);
    ASSERT_FALSE(F == G);
    ASSERT_TRUE(F != G);
}
TEST(test_card_type) {
    Card three_spades = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(three_spades.is_face());
}
TEST(test_is_face) {
    Card three_spades = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(three_spades.is_face());
}
TEST(test_get_suit) {
    Card three_spades = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(three_spades.get_suit(Card::SUIT_SPADES), Card::SUIT_SPADES);
}
TEST(test_card_ctor2) {
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}
TEST(test_card_insertion) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}
// Add more test cases here

TEST_MAIN()
