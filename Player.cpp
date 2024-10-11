#include "Player.hpp"
#include <cassert>
#include <vector>

using namespace std;


class SimplePlayer : public Player {
public:
    SimplePlayer(string name_in)
     : name(name_in) {
    }
    const std::string & get_name() const override {
        return this->name;
    }
    void add_card(const Card &c) override{
        this -> hand.push_back(c);
    }
    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override {
        if (round == 1){
            int count = 0;
            for (int i = 0; i < hand.size(); i++){
                if (this->hand[i].is_left_bower(upcard.get_suit())){
                    count++;
                } 
                else if (this->hand[i].is_right_bower(upcard.get_suit())){
                    count++;
                } 
                else if (this->hand[i].is_trump(upcard.get_suit()) == true && 
                (this->hand[i].get_rank() == QUEEN || 
                this->hand[i].get_rank() == KING || 
                this->hand[i].get_rank() == ACE)
                ){
                    count++;
                }
            }
            if (count >= 2){
                order_up_suit = upcard.get_suit();
                return true;
            }
            else{
                return false;
            }
        }
        if (round == 2){
            if (is_dealer == true){
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            else{ 
                int count = 0;
                for (int i = 0; i < hand.size(); i++){
                    if (this->hand[i].is_left_bower(Suit_next(upcard.get_suit()))){
                        count++;
                    } 
                    else if (this->hand[i].is_right_bower(Suit_next(upcard.get_suit()))){
                        count++;
                    } 
                    else if (this->hand[i].is_trump(Suit_next(upcard.get_suit())) == true && 
                    (this->hand[i].get_rank() == QUEEN || 
                    this->hand[i].get_rank() == KING || 
                    this->hand[i].get_rank() == ACE)
                    ){
                        count++;
                    }
                }
                if (count >=1){
                    order_up_suit = Suit_next(upcard.get_suit());
                    return true;
                }
                else{
                    return false;
                }
            }
        }
        else{
            return false;
        }
    }
    void add_and_discard(const Card &upcard) override {
        Card lowest = upcard;
        Card discard = upcard;
        for(int i = 0; i < MAX_HAND_SIZE; i++){
            if (Card_less(this->hand[i], lowest, upcard.get_suit())) {
                discard = this->hand[i];
                this->hand[i] = lowest;
                lowest = discard;
            }
        }
    }
    Card lead_card(Suit trump) override {
        Card play;
        bool all_trump = true;
        for (int i = 0; i < this -> hand.size(); i++){
            if (this -> hand[i].get_suit() != trump && !this->hand[i].is_left_bower(trump)){
                all_trump = false;
            }
        }
        if (all_trump == true){
            play = this -> hand[0];
            for (int i = 0; i < this -> hand.size(); i++){
                if (Card_less(play, this -> hand[i], trump)){
                    play = this -> hand[i];
                }
            }
            return play;
        } 
        else{
            for (int i = 0; i < this -> hand.size(); i++){
                if (this -> hand[i].get_suit() != trump && !this->hand[i].is_left_bower(trump)){
                    play = this -> hand[i];
                }
            }
            for (int i = 0; i < this -> hand.size(); i++){
                if (Card_less(play, this -> hand[i],trump) == true && this -> hand[i].get_suit() != trump && !this->hand[i].is_left_bower(trump)){
                    play = this -> hand[i];
                }
            }
            return play;
        }
    }
    Card play_card(const Card &led_card, Suit trump) override {
        Card play;
        bool have_suit = false;
        for (int i = 0; i < this -> hand.size(); i++){
            if (this -> hand[i].get_suit(trump) == led_card.get_suit(trump)){
                have_suit  = true;
                play = this->hand[i];
            }
        }
        if (have_suit == true){
            for (int i = 0; i < this -> hand.size(); i++){
                if (Card_less(play, this->hand[i], trump) && 
                this -> hand[i].get_suit(trump) == led_card.get_suit(trump)){
                    play = this -> hand[i];
                }
            }
            return play;
        }
        else{
            play = this -> hand[0];
            for (int i = 0; i < this -> hand.size(); i++){
                if (Card_less(this->hand[i], play, trump)){
                    play = this -> hand[i];
                }
            }
            return play;
        }
    }
    private:
        std::vector<Card> hand;
        string name;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(string name_in)
     : name(name_in) {
    }
    const std::string & get_name() const override {
        return this->name;
    }
    void add_card(const Card &c) override{
        this -> hand.push_back(c);
    }
    
    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override{
        return false;
    }

    void add_and_discard(const Card &upcard) override {

    }

    Card lead_card(Suit trump) override {
        return  Card(TWO, SPADES);
    }

    Card play_card(const Card &led_card, Suit trump) override {
        return  Card(TWO, SPADES);
    }

    private:
        std::vector<Card> hand;
        string name;
};


Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
    if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
    }
  // Repeat for each other type of Player
    if (strategy == "Human"){
       // return new HumanPlayer(name);
       return new HumanPlayer(name);

    }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  return os << p.get_name();
}
