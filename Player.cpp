#include "Card.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <cassert>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

class Simple : public Player {
public:

    Simple(string name)
    : playerName(name) {}

    const string & get_name() const override {
        return playerName;
    }

    void add_card(const Card &c) override {
        //assert(playerHand.size() < MAX_HAND_SIZE);
        playerHand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit)
    const override {
        assert(round == 1 || round == 2);

        int counter = 0;
        if(round == 1) {
            for( int i = 0; i < static_cast<int>(playerHand.size()); ++i) {
                if(playerHand[i].is_trump(upcard.get_suit())
                    && playerHand[i].is_face()) {
                    ++counter;
                }
            }
            if(counter >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else {
                return false;
            }
        }
        else if(round == 2) {
            if(is_dealer == true) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            for(int i = 0; i < static_cast<int>(playerHand.size()); ++i) {
                if (playerHand[i].is_trump(Suit_next(upcard.get_suit()))
                    && playerHand[i].is_face()) {
                    ++counter;
                }
            }
            if(counter >= 1) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            } 
            else {
                return false;
            }
        }
        return false;
    }

    void add_and_discard(const Card &upcard) override {
        assert(playerHand.size() > 0);

        int lowestIndex = 0;
        add_card(upcard);

        for(int i = 1; i < static_cast<int>(playerHand.size()); ++i) {
            if (Card_less(playerHand[i], playerHand[lowestIndex],
                upcard.get_suit()) ) {
                lowestIndex = i;
            }
        }
        playerHand.erase(playerHand.begin() + lowestIndex);
    }

Card lead_card(const string &trump) override {
    assert(playerHand.size() > 0);

    bool haveNonTrump = false;
    Card cardTrack;
    int cardTrackNum = 0;
    
    for(int i = 0; i < static_cast<int>(playerHand.size()); ++i) {
        if(!playerHand[i].is_trump(trump)) {
            haveNonTrump = true;
        }
    }
    if(haveNonTrump) {
        for(int i = 0; i < static_cast<int>(playerHand.size()); ++i) {
            if(!playerHand[i].is_trump(trump)) {
                cardTrack = playerHand[i];
                cardTrackNum = i;
                break;
            }
        }
        for(int i = 0; i < int(playerHand.size()); ++i) {
            if(!playerHand[i].is_trump(trump) && Card_less(cardTrack,
            playerHand[i],trump)) {
                cardTrack = playerHand[i];
                cardTrackNum = i;
            }
        }
    }
    else if (!haveNonTrump) {
        cardTrack = playerHand[0];
        for (int i = 1; i < int(playerHand.size()); ++i) {
            if(Card_less(cardTrack ,playerHand[i],trump)) {
                cardTrack = playerHand[i];
                cardTrackNum = i;
            }
        }
    }
    playerHand.erase(playerHand.begin() + cardTrackNum);
    return cardTrack;
}

    Card play_card(const Card &led_card, const string &trump) override {
        assert(playerHand.size() > 0);
        
        bool canFollowSuit = false;
        Card cardTrack = playerHand[0];
        int cardTrackNum = 0;
        for(int i = 0; i < int(playerHand.size()); ++i) {
            if(playerHand[i].get_suit(trump) == led_card.get_suit(trump)) {
                canFollowSuit = true;
            }
        }
        if(canFollowSuit) {
            for(int i = 0; i < int(playerHand.size()); ++i) {
                if(playerHand[i].get_suit(trump) == led_card.get_suit(trump)) {
                    cardTrack = playerHand[i];
                    cardTrackNum = i;
                    break;
                }
            }
            for(int i = 0; i < int(playerHand.size()); ++i) {
                if(playerHand[i].get_suit(trump) == led_card.get_suit(trump) &&
                   Card_less(cardTrack,playerHand[i],led_card,trump)) {
                    cardTrack = playerHand[i];
                    cardTrackNum = i;
                }
            }
        }
        else {
            for(int i = 1; i < int(playerHand.size()); ++i) {
                if(Card_less(playerHand[i], cardTrack, trump)) {
                    cardTrack = playerHand[i];
                    cardTrackNum = i;
                }
            }
        }
        playerHand.erase(playerHand.begin() + cardTrackNum);
        return cardTrack;
    }
    
protected:
    string playerName;
    vector<Card> playerHand;
};

class Human : public Player {
 public:

    Human (string name) 
    : playerName(name) {}

    const string & get_name() const override {
        return playerName;
    }

    void add_card(const Card &c) override {
        assert(playerHand.size() < MAX_HAND_SIZE);
        playerHand.push_back(c);
        sort(playerHand.begin(), playerHand.end());
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit)
    const override {
        assert(round == 1 || round == 2);
        
        string input;

        for(int i = 0; i < static_cast<int>(playerHand.size()); ++i) {
            cout << "Human player " << playerName << "\'s hand: [" << i << "] "
                 << playerHand[i] << endl;
        }
        cout << "Human player " << playerName
             << ", please enter a suit, or \"pass\":" << endl;
        cin >> input;
        
        if(input == "pass") {
            return false;
        }
        else if(input == "Spades") {
            order_up_suit = "Spades";
            return true;
        }
        else if(input == "Hearts") {
            order_up_suit = "Hearts";
            return true;
        }
        else if(input == "Clubs") {
            order_up_suit = "Clubs";
            return true;
        }
        else if(input == "Diamonds") {
            order_up_suit = "Diamonds";
            return true;
        }
        return 1;
    }

    void add_and_discard(const Card &upcard) override {
        assert(playerHand.size() > 0);
        sort(playerHand.begin(), playerHand.end());

        int cardNum = 0;
        
        for (int i = 0; i < static_cast<int>(playerHand.size()); ++i) {
            cout << "Human player " << playerName <<"'s hand: ["
            << i << "] " << playerHand[i] << endl;
        }
        cout << "Discard upcard: [-1]" << endl
             << "Human player " << playerName
             << ", please select a card to discard:" << endl << endl;
        cin >> cardNum;
        assert((cardNum == -1) ||
               (cardNum < static_cast<int>(playerHand.size())));
        if(cardNum != -1) {
            playerHand.erase(playerHand.begin() + cardNum);
            add_card(upcard);
        }
    }

    virtual Card lead_card(const std::string &trump) override {
        assert(playerHand.size() > 0);
        sort(playerHand.begin(), playerHand.end());

        Card card;
        int cardNum = 0;

        for (int i = 0; i < static_cast<int>(playerHand.size()); ++i) {
            cout << "Human player " << playerName <<"'s hand: ["
            << i << "] " << playerHand[i] << endl;
        }
        cout << "Human player " << playerName
        << ", please select a card:" << endl;
        cin >> cardNum;
        assert(-1 < cardNum ||cardNum < static_cast<int>(playerHand.size()));
        
        card = playerHand[cardNum];
        playerHand.erase(playerHand.begin() + cardNum);

        return card;
    }
    
    virtual Card play_card(const Card &lead_card, const std::string &trump)
    override {
        assert(playerHand.size() > 0);
        sort(playerHand.begin(), playerHand.end());

        Card card;
        int cardNum = 0;

        for (int j = 0; j < static_cast<int>(playerHand.size()); ++j) {
            cout << "Human player " << playerName << 
            "'s hand: [" << j << "] " << 
            playerHand[j] << endl;
        }
        cout << "Human player " << playerName
        << ", please select a card:" << endl;
        cin >> cardNum;
        assert(-1 < cardNum || cardNum < static_cast<int>(playerHand.size()));
        
        card = playerHand[cardNum];
        playerHand.erase(playerHand.begin()+cardNum);

        return card;
    }
private:
    string playerName;
    vector<Card> playerHand;
};

Player * Player_factory(const std::string &name, const std::string &strategy) {
    if (strategy == "Simple") {
        return new Simple(name);
    }
    if (strategy == "Human") {
        return new Human(name);
    }
    assert(false);
    return nullptr;
}

ostream & operator<<(ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}
