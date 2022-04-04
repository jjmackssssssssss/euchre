// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <sstream>
using namespace std;

// THESE TEST CASES WILL ONLY TELL YOU IF YOUR CODE COMPILES.
// YOU NEED TO WRITE YOUR OWN COMPREHENSIVE TEST CASES IN Player_tests.cpp

TEST(test_player_insertion) {
  Player * human = Player_factory("NotRobot", "Human");
  ostringstream oss;
  oss << * human;
  ASSERT_EQUAL(oss.str(), "NotRobot");
  oss.str("");
  Player * alice = Player_factory("Alice", "Simple");
  oss << *alice;
  ASSERT_EQUAL(oss.str(), "Alice");
  delete alice;
  delete human;
}

TEST(test_player_get_name) {
  Player * alice = Player_factory("Alice", "Simple");
  ASSERT_EQUAL(alice->get_name(), "Alice");
  delete alice;
}

static void add_cards(Player *player) {
  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  for (int i = 0; i < 5; ++i) {
    player->add_card(two_spades);
  }
}
static void add_cards2(Player *player) {
  Card two_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
  for (int i = 0; i < 5; ++i) {
    player->add_card(two_spades);
  }
}
static void add_cards3(Player *player) {
  Card two_spades = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  for (int i = 0; i < 5; ++i) {
    player->add_card(two_spades);
  }
}
static void add_cards4(Player *player) {
  Card two_spades = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  for (int i = 0; i < 3; ++i) {
    player->add_card(two_spades);
  }
    Card three_spades = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    for (int i = 0; i < 2; ++i) {
      player->add_card(three_spades);
    }
}
static void add_cards6(Player *player) {
    player->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    player->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    player->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    player->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    player->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  }
static void add_cards7(Player *player) {
  player->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  player->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  player->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
  player->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  player->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
}
static void add_cards5(Player *player) {
  Card two_spades = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  for (int i = 0; i < 3; ++i) {
    player->add_card(two_spades);
  }
    Card three_spades = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    for (int i = 0; i < 2; ++i) {
      player->add_card(three_spades);
    }
}
static void add_cards8(Player *player) {
  player->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
  player->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  player->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  player->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
  player->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
}
static void add_cards9(Player *player) {
  player->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
  player->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  player->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  player->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  player->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
}

TEST(test_simple_player_make_trump) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
    //첫번째FALSE 되는 케이스 
}
TEST(test_simple_player_make_trump2) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      false,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
    //2번째 FALSE CASE
}
TEST(test_simple_player_make_trump3) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      false,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}
TEST(test_simple_player_make_trump4) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards2(bob);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}
TEST(test_simple_player_make_trump5) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards2(bob);

  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      false,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

  delete bob;
}
TEST(test_simple_player_make_trump6) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards5(bob);
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      false,           //Bob is also the dealer
      1,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete bob;
}
TEST(test_simple_player_make_trump7) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards5(bob);
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_SPADES;
  bool orderup = bob->make_trump(
      nine_spades,    //upcard
      true,           //Bob is also the dealer
      2,              //first round
      trump           //suit ordered up (if any)
  );
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

  delete bob;
}

TEST(test_simple_player_lead_card) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);
  Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_SPADES);
  ASSERT_EQUAL(card_led, nine_spades); //check led card
  delete bob;
}

TEST(test_simple_player_lead_card2) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards2(bob);
    Card nine_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_DIAMONDS);
  ASSERT_NOT_EQUAL(card_led, nine_spades); //check led card
  delete bob;
}
TEST(test_simple_player_lead_card3) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);
    Card nine_spades(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_DIAMONDS);
  ASSERT_NOT_EQUAL(card_led, nine_spades); //check led card
  delete bob;
}
TEST(test_simple_player_lead_card4) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards3(bob);
    Card nine_spades(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_DIAMONDS);
  ASSERT_NOT_EQUAL(card_led, nine_spades); //check led card
  delete bob;
}
TEST(test_simple_player_lead_card5) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards6(bob);
    Card nine_spades(Card::RANK_ACE, Card::SUIT_HEARTS);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_DIAMONDS);
    Card nine_spades2(Card::RANK_ACE, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, nine_spades2); //check led card
  delete bob;
}
TEST(test_simple_player_lead_card6) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards7(bob);
    Card nine_spades(Card::RANK_ACE, Card::SUIT_HEARTS);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_DIAMONDS);
    Card nine_spades2(Card::RANK_ACE, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, nine_spades2); //check led card
  delete bob;
}
TEST(test_simple_player_lead_card7) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards7(bob);
    Card nine_spades(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_CLUBS);
    Card nine_spades2(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_led, nine_spades2); //check led card
  delete bob;
}
TEST(test_simple_player_lead_card8) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards8(bob);
    Card nine_spades(Card::RANK_JACK, Card::SUIT_HEARTS);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_DIAMONDS);
    Card nine_spades2(Card::RANK_JACK, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, nine_spades2); //check led card
  delete bob;
}
TEST(test_simple_player_lead_card9) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards9(bob);
    Card nine_spades(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  bob->add_and_discard(nine_spades);
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);
    Card nine_spades2(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_led, nine_spades2); //check led card
  delete bob;
}

TEST(test_simple_player_play_card) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards(bob);
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump = Card::SUIT_HEARTS;
  Card card_played = bob->play_card(nine_diamonds, trump); //Diamonds is led
  Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
  ASSERT_EQUAL(card_played, two_spades);
  delete bob;
}
TEST(test_simple_player_play_card2) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards4(bob);
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump = Card::SUIT_HEARTS;
  Card card_played = bob->play_card(nine_diamonds, trump); //Diamonds is led
  Card two_spades = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_played, two_spades);
  delete bob;
}
TEST(test_simple_player_play_card3) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards4(bob);
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_SPADES);
  string trump = Card::SUIT_HEARTS;
  Card card_played = bob->play_card(nine_diamonds, trump); //Diamonds is led
  Card two_spades = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  ASSERT_EQUAL(card_played, two_spades);
  delete bob;
}
TEST(test_simple_player_play_card4) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards4(bob);
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump = Card::SUIT_DIAMONDS;
  Card card_played = bob->play_card(nine_diamonds, trump); //Diamonds is led
  Card two_spades = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  ASSERT_NOT_EQUAL(card_played, two_spades);
  delete bob;
}
TEST(test_simple_player_play_card5) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards4(bob);
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  string trump = Card::SUIT_DIAMONDS;
  Card card_played = bob->play_card(nine_diamonds, trump); //Diamonds is led
  Card two_spades = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
  ASSERT_NOT_EQUAL(card_played, two_spades);
  delete bob;
}
TEST(test_simple_player_play_card6) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards6(bob);
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump = Card::SUIT_DIAMONDS;
  Card card_played = bob->play_card(nine_diamonds, trump); //Diamonds is led
  Card two_spades = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
  ASSERT_NOT_EQUAL(card_played, two_spades);
  delete bob;
}
TEST(test_simple_player_play_card7) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards6(bob);
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump = Card::SUIT_DIAMONDS;
  Card card_played = bob->play_card(nine_diamonds, trump); //Diamonds is led
  Card two_spades = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, two_spades);
  delete bob;
}
TEST(test_simple_player_play_card8) {
  Player * bob = Player_factory("Bob", "Simple");
  add_cards9(bob);
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_HEARTS);
  string trump = Card::SUIT_DIAMONDS;
  Card card_played = bob->play_card(nine_diamonds, trump); //Diamonds is led
  Card two_spades = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_played, two_spades);
  delete bob;
}


TEST_MAIN()
