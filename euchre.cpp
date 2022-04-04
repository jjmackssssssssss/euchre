#include "Card.h"
#include "Pack.h"
#include "Player.h"
#include "string.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <array>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Game {
public:
    // constructor
    Game(istream& pack_input)
    : pack(pack_input), hand(0), dealerIndex(0), teamOneTrick(0),
    teamTwoTrick(0),
    teamOne_point(0), teamTwo_point(0), orderedUpTeam(1), leadPlayerIndex(0)
    {}

    //EFFECTS adds value to point
    void setint(int &point, const int value) {
        point += value;
    }


    void set_dealerIndex() {
        ++dealerIndex;
        if(dealerIndex == 4) {
            dealerIndex = 0;
        }
    }

    int get_dealerIndex() const {
        return dealerIndex;
    }

    void set_teamOneTrick() {
        ++teamOneTrick;
    }

    void reset_teamOneTrick() {
        teamOneTrick = 0;
    }

    int get_teamOneTrick() const {
        return teamOneTrick;
    }

    void set_teamTwoTrick() {
        ++teamTwoTrick;
    }

    void reset_teamTwoTrick() {
        teamTwoTrick = 0;
    }

    int get_teamTwoTrick() const {
        return teamTwoTrick;
    }

    void set_teamOne_point() {
        ++teamOne_point;
    }

    int get_teamOne_point() const {
        return teamOne_point;
    }

    void set_teamTwo_point() {
        ++teamTwo_point;
    }

    int get_teamTwo_point() const {
        return teamTwo_point;
    }

    void set_hand() {
        ++hand;
    }

    int get_hand() const {
        return hand;
    }

    void set_orderedUpTeam(const int orderedupteam) {
        orderedUpTeam = orderedupteam;
    }

    int get_orderedUpTeam() const {
        return orderedUpTeam;
    }

    void set_upcard(const Card input_upcard) {
        upcard = input_upcard;
    }

    Card get_upcard() const {
        return upcard;
    }

    void set_pack(const Pack input_pack) {
        pack = input_pack;
    }

    Pack get_pack() const {
        return pack;
    }

    void reset_pack() {
        pack.reset();
    }

    void shuffle_pack(const string shuffleOrNot) {
        if(shuffleOrNot == "shuffle") {
            pack.shuffle();
        }
        else {
            pack.reset();
        }
    }   

    Card deal_card() {
        return pack.deal_one();
    }

    void set_leadPlayerIndex(const int lpi) {
        leadPlayerIndex = lpi;
    }
    
    int get_leadPlayerIndex() const {
        return leadPlayerIndex;
    }

    void set_ledcard(const Card led_card) {
        ledcard = led_card;
    }

    Card get_ledcard() const {
        return ledcard;
    }

    void set_playedcard(const Card played_card) {
        playedcard = played_card;
    }

    Card get_playedcard() const {
        return playedcard;
    }

    void set_onetrickCards(const Card input_card) {
        onetrick.onetrickCards.push_back(input_card);
    }

    Card get_onetrickCards(const int index) const {
        return onetrick.onetrickCards.at(index);
    }

    void set_onetrickPlayerIndex(const int index) {
        onetrick.onetrickPlayerIndex.push_back(index);
    }

    int get_onetrickPlayerIndex(const int index) const {
        return onetrick.onetrickPlayerIndex.at(index);
    }

    void set_trump(const string in_trump) {
        trump = in_trump;
    }
    
    string get_trump() const {
        return trump;
    }

    void set_order_up_suit(const string order_up_suit) {
        orderUpSuit = order_up_suit;
    }

    string get_order_up_suit() const {
        return orderUpSuit;
    }

    void reset_onetrick () {
        onetrick.onetrickCards.clear();
        onetrick.onetrickPlayerIndex.clear();
    }

protected:
    string trump;
    string orderUpSuit;
    Card upcard;
    Card ledcard;
    Card playedcard;
    OneTrick onetrick;
    Pack pack;
    int hand;
    int dealerIndex;
    int teamOneTrick;
    int teamTwoTrick;
    int teamOne_point;
    int teamTwo_point;
    int orderedUpTeam;
    int leadPlayerIndex;
};

void print_error() {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
}
void one_trick(Game * game, vector<Player*> &players, int & start_index);

void determine_trick_taker(Game * game, vector<Player*> &players,
                           int & start_index);

void determine_trick_winner(Game * game, vector<Player*> players);

void one_hand(Game * game, vector<Player*> players, int & start_index) {
    one_trick(game, players, start_index);
    determine_trick_taker(game, players, start_index);
    one_trick(game, players, start_index);
    determine_trick_taker(game, players, start_index);
    one_trick(game, players, start_index);
    determine_trick_taker(game, players, start_index);
    one_trick(game, players, start_index);
    determine_trick_taker(game, players, start_index);
    one_trick(game, players, start_index);
    determine_trick_taker(game, players, start_index);
    determine_trick_winner(game, players);
}

void reset_everything(Game * game) {
    game->reset_onetrick();
    game->reset_pack();
    game->reset_teamOneTrick();
    game->reset_teamTwoTrick();
    game->set_dealerIndex();
    game->reset_pack();
    game->set_hand();
}

// MODIFIES: start_index
// EFFECTS: increase start_index by one
void increase_start_index(int &start_index) {
    ++start_index;
    if(start_index == 4) {
            start_index = 0;
    }
}

void increase_start_index(int &start_index, const int dealer_index) {
    start_index = dealer_index + 1;
    if(start_index == 4) {
            start_index = 0;
    }
}

// EFFECTS: returns true if playerName == dealerName
bool is_dealer (string playerName, string dealerName) {
    if(playerName == dealerName) {
        return true;
    }
    else {
        return false;
    }
}
// MODIFIES: pack
// EFFECTS: shuffle the card
void shuffle_pack (Game * game, Pack &pack, const string shuffleOrNot) {
    if(shuffleOrNot == "shuffle") {
        pack.shuffle();
    }
    else {
        pack.reset();
    }
}

void deal_batch(Game * game, vector<Player*> players,
                const int repeatNum, int &start_index) {
    for(int i = 0; i < repeatNum; ++i) {
        players.at(start_index)->add_card(game->deal_card());
    }
    ++start_index;
    if(start_index == 4) {
        start_index = 0;
    }
}

void deal_batches(Game * game, vector<Player*> players,
                int &start_index) {
    deal_batch(game, players, 3, start_index);
    deal_batch(game, players, 2, start_index);
    deal_batch(game, players, 3, start_index);
    deal_batch(game, players, 2, start_index);
    deal_batch(game, players, 2, start_index);
    deal_batch(game, players, 3, start_index);
    deal_batch(game, players, 2, start_index);
    deal_batch(game, players, 3, start_index);
}
// EFFECTS: deal cards and return the upcard
Card deal_card(Game * game, vector<Player*> players, int dealer_index) {
    int startIndex = 0;
    if(dealer_index == 0) {
        startIndex = 1;
        deal_batches(game, players, startIndex);
    }
    else if(dealer_index == 1) {
        startIndex = 2;
        deal_batches(game, players, startIndex);
    }
    else if(dealer_index == 2) {
        startIndex = 3;
        deal_batches(game, players, startIndex);
    }
    else {
        startIndex = 0;
        deal_batches(game, players, startIndex);
    }
    return game->deal_card();
}

// EFFECTS: at the beginning of each hand, announce the hand
void announce_Hand(Game * game, vector<Player*> players, const Card upcard) {
    cout << "Hand " << game->get_hand() << endl;
    cout << players.at(game->get_dealerIndex())->get_name()
    << " deals" << endl;
    cout << upcard << " turned up" << endl;
}

void making_trump(Game * game, vector<Player*> players, int & start_index,
                  const Card upcard) {
    string order_up_suit;
    int round = 1;
    bool trump_is_set = false;
    for(int i = 0; i < 4; ++i) {
        trump_is_set = players.at(start_index)->make_trump(upcard,
                            is_dealer(players.at(start_index)->get_name(),
                            players.at(game->get_dealerIndex())->get_name()),
                                round, order_up_suit);
        if(trump_is_set) {
        
            cout << players.at(start_index)->get_name() << " orders up "
                 << order_up_suit << endl;
            players.at(game->get_dealerIndex())->add_and_discard(upcard);
            break;
        }
        cout << players.at(start_index)->get_name() << " passes" << endl;
        increase_start_index(start_index);
    }
    if(!trump_is_set) {
        ++round;
    }
    
    if(round == 2) {
        increase_start_index(start_index, game->get_dealerIndex());
        trump_is_set = players.at(start_index)->
                make_trump(upcard,
                is_dealer(players.at(start_index)->get_name(),
                players.at(game->get_dealerIndex())->get_name()),
                round,
                order_up_suit);
        while(!trump_is_set) {
            cout << players.at(start_index)->get_name() << " passes" << endl;
            increase_start_index(start_index);
            trump_is_set = players.at(start_index)->
                make_trump(upcard,
                is_dealer(players.at(start_index)->get_name(),
                players.at(game->get_dealerIndex())->get_name()),
                round, order_up_suit);
        }
        cout << players.at(start_index)->get_name() << " orders up "
                 << order_up_suit << endl << endl;
    }
    if(start_index == 0 || start_index == 2) {
        game->set_orderedUpTeam(1);
    }
    else {
        game->set_orderedUpTeam(2);
    }
    game->set_trump(order_up_suit);
}

// MODIFIES: players
// EFFECTS: delete players after the game
void deletePlayers(vector<Player*> &players) {
    //delete players;
    for (int i = 0; i < int(players.size()); ++i) {
        delete players[i];
    }
}

// EFFECTS: announce each round of the hand
void one_trick(Game * game, vector<Player*> &players, int & start_index) {
    game->set_leadPlayerIndex(start_index);
    game->set_ledcard(players.at(start_index)->lead_card(game->get_trump()));
    game->set_onetrickCards(game->get_ledcard());
    game->set_onetrickPlayerIndex(start_index);
    cout << game->get_ledcard() << " led by "
         << players.at(start_index)->get_name() << endl;
    for(int i = 0; i < 3; ++i) {
    increase_start_index(start_index);
    game->set_playedcard(players.at(start_index)->
        play_card(game->get_ledcard(),game->get_trump()));
    game->set_onetrickCards(game->get_playedcard());
    game->set_onetrickPlayerIndex(start_index);
    cout << game->get_playedcard() << " played by "
         <<players.at(start_index)->get_name() << endl;
    }
}

void determine_trick_taker(Game * game, vector<Player*> &players,
                           int & start_index) {
    int highestCardIndex = 0;
    for(int i = 1; i < 4; ++i) {
        if(Card_less(game->get_onetrickCards(highestCardIndex),
            game->get_onetrickCards(i), game->get_ledcard(),
                     game->get_trump())) {
            highestCardIndex = i;
        }
    }
    start_index = game->get_onetrickPlayerIndex(highestCardIndex);
    if(game->get_onetrickPlayerIndex(highestCardIndex) == 0 || 
       game->get_onetrickPlayerIndex(highestCardIndex) == 2) {
        cout << players.at(game->get_onetrickPlayerIndex(highestCardIndex))
        ->get_name()
             << " takes the trick" << endl << endl;
        game->set_teamOneTrick();
        start_index = game->get_onetrickPlayerIndex(highestCardIndex);
    }
    else {
        cout << players.at(game->get_onetrickPlayerIndex(highestCardIndex))
        ->get_name()
             << " takes the trick" << endl << endl;
        game->set_teamTwoTrick();
        start_index = game->get_onetrickPlayerIndex(highestCardIndex);
    }
    game->reset_onetrick();
}

void play_one_hand(Game * game, vector<Player*> &players, int & start_index) {

    for(int i = 0; i < 5; ++i) {
        one_trick(game, players, start_index);
        determine_trick_taker(game, players, start_index);
    }
}

void set_team_one_point_twice(Game * game) {
    game->set_teamOne_point();
    game->set_teamOne_point();
}

void set_team_two_point_twice(Game * game) {
    game->set_teamTwo_point();
    game->set_teamTwo_point();
}
// EFFECTS: announce winner of a trick
void determine_trick_winner(Game * game, vector<Player*> players) {
    if(game->get_teamOneTrick() > game->get_teamTwoTrick()) {
        cout << players.at(0)->get_name() << " and " 
             << players.at(2)->get_name() << " win the hand" << endl;
        if(game->get_orderedUpTeam() == 1) {
            if(game->get_teamOneTrick() == 5) {
                set_team_one_point_twice(game);
                cout << "march!" << endl;}
            else {
                game->set_teamOne_point();
            }
        }
        else {
            set_team_one_point_twice(game);
            cout << "euchred!" << endl;
        }
    }
    else{
        cout << players.at(1)->get_name() << " and " 
             << players.at(3)->get_name() << " win the hand" << endl;
        if(game->get_orderedUpTeam() == 2) {
            if(game->get_teamTwoTrick() == 5) {
                set_team_two_point_twice(game);
                cout << "march!" << endl; 
            }
            else {
                game->set_teamTwo_point();
            }
        }
        else {
            set_team_two_point_twice(game);
            cout << "euchred!" << endl;
        }
    }
    cout << players.at(0)->get_name() << " and " << players.at(2)->get_name()
         << " have " << game->get_teamOne_point() << " points" << endl;
    cout << players.at(1)->get_name() << " and " << players.at(3)->get_name()
         << " have " << game->get_teamTwo_point() << " points" << endl << endl;
}

void the_game(Game * game, vector<Player*>&players,
            Card&upcard, int&start_index) {
    start_index = game->get_dealerIndex() + 1;
        if(start_index == 4) {
            start_index = 0;
    }
    announce_Hand(game, players, upcard);
    making_trump(game, players, start_index, upcard);
    increase_start_index(start_index, game->get_dealerIndex());
    one_hand(game, players, start_index);
    reset_everything(game);
}
int main(int argc, char* argv[]) {
    if(argc != 12 || atoi(argv[3]) < 1 || atoi(argv[3]) > 100 ||
        strcmp(argv[2], "shuffle") !=0) {
        if(strcmp(argv[2], "noshuffle") != 0) {
            print_error();
            return 1;
        }
    }
    for(int i = 5; i < argc; i += 2) {
        if(strcmp(argv[i], "Simple") !=0) {
            if(strcmp(argv[i], "Human") != 0) {
                print_error();
                return 1;
            }
        }
    }
    ifstream input;
    string inputFileName = argv[1];
    (input).open(inputFileName);
    if(!(input.is_open())) {
        cout << "Error opening " << inputFileName << endl;
        return 1;
    }
    Game * game = new Game(input);
    vector <Player*> players;
    Card upcard;
    int start_index = 0;

    players.push_back(Player_factory(argv[4], argv[5]));
    players.push_back(Player_factory(argv[6], argv[7]));
    players.push_back(Player_factory(argv[8], argv[9]));
    players.push_back(Player_factory(argv[10], argv[11]));
    
    for(int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;

    while(game->get_teamOne_point() < atoi(argv[3]) &&
        game->get_teamTwo_point() < atoi(argv[3])) {
        game->shuffle_pack(argv[2]);
        upcard = deal_card(game, players, game->get_dealerIndex());
        the_game(game, players, upcard, start_index);
    }
    if(game->get_teamOne_point() >= atoi(argv[3])) {
        cout << argv[4] << " and " << argv[8] << " win!" << endl;
    }
    else if (game->get_teamTwo_point() >= atoi(argv[3])){
        cout << argv[6] << " and " << argv[10] << " win!" << endl;
    }
    else {
        return 1;
    }
    deletePlayers(players);
}


