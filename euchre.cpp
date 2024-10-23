#include <iostream>
#include <cassert>
#include <vector>
#include "Pack.hpp"
#include "Player.hpp"

using namespace std;

#include <iostream>
using namespace std;

struct in_data {
  string shuffle;
  int points;
  string name1;
  string name2;
  string name3;
  string name4;
  string strat1;
  string strat2;
  string strat3;
  string strat4;
};

class Game { 
  public:   
  Game(in_data data){
    this->points = data.points;
    this->dealer = 0;
    if (data.shuffle == "shuffle"){
      this->shuf = true;
    }
    else{
      this->shuf = false;
    }
    this->players.push_back(Player_factory(data.name1,data.strat1));
    this->players.push_back(Player_factory(data.name2,data.strat2));
    this->players.push_back(Player_factory(data.name3,data.strat3));
    this->players.push_back(Player_factory(data.name4,data.strat4));
  }; 

  void play(){
    while (this->score0_2 < this->points && this->score1_3 < this->points){
      cout << "Hand " << this->hand << endl;
      if (this->shuf){
        this->pack.shuffle();
      }
      deal();
      make_trump();
      leader = (this->dealer+1)%4;
      this->trick0_2 = 0;
      this->trick1_3 = 0;
      for (int i = 0; i < 5; i++){
        int play_trick = trick();
        trick_winner(play_trick);
      }
      hand_winner();
      cout << this->players[0]->get_name() << " and " << 
      this->players[2]->get_name() << " have " << this->score0_2 << " points" << endl;
      cout << this->players[1]->get_name() << " and " << 
      this->players[3]->get_name() << " have " << this->score1_3 << " points" << endl;
      cout << endl;
      this->dealer = (this->dealer+1)%4; 
      this->hand++;
      this->pack.reset();
    }
    if (this->score0_2 > this->score1_3){
      cout << this->players[0]->get_name() << " and " << 
      this->players[2]->get_name() << " win!" << endl;
    }
    else{
      cout << this->players[1]->get_name() << " and " << 
      this->players[3]->get_name() << " win!" << endl;
    }
    for(size_t i = 0; i < players.size(); ++i){   
      delete this->players[i]; 
    }
  }

  private:   
  std::vector<Player*> players;   
  Pack pack;   // ...
  int points;
  int dealer = 0;
  int leader;
  //Scores
  int trick0_2 = 0;
  int trick1_3 = 0;
  int score0_2 = 0;
  int score1_3 = 0; 
  //Hand score
  int hand = 0;
  int round = 1;
  int order_up;
  bool shuf;
  Card upcard;
  Suit trump;
  //Shuffles Deck
  void shuffle(){
    //cout << "shuffling deck" << endl;
    this->pack.shuffle();
  };   
  //Deals cards 
  void deal(){
    //Identify dealer
    cout << this->players[this->dealer]->get_name() << " deals" << endl;
    //Begin with player to the left of them
    for(int i = 0; i< 8; i++){
      int offset = ((this->dealer+1+i)%4);
      if ((i%2 == 0 && i<4) || (i%2 == 1 && i>=4)){
        //cout << 3 << " " << "offset: " << offset << endl;
        this->players[offset]->add_card(this->pack.deal_one());
        this->players[offset]->add_card(this->pack.deal_one());
        this->players[offset]->add_card(this->pack.deal_one());
      }
      else if ((i%2 == 1 && i<4) || (i%2 == 0 && i>=4)){
        //cout << 2 << " " << "offset: " << offset << endl;
        this->players[offset]->add_card(this->pack.deal_one());
        this->players[offset]->add_card(this->pack.deal_one());
      }
    }
    for(int i = 0; i< 4; i++){
      //cout << "player" << i << ": " << endl;
      //this->players[i]->show_cards();
    }
  };   
  //Round to determine who gets trump
  void make_trump(){
    Card upcard = this->pack.deal_one();
    cout << upcard.get_rank() << " of " << upcard.get_suit() << " turned up" << endl;
    this->trump = upcard.get_suit();
    this->round = 1;
    int orderer = 0;
    for (int i = 0; i < 8; i++){
      if(i > 3){
        this->round = 2;
      }
      bool is_dealer;
      if ((this->dealer+1+i)%4 == this->dealer){
        is_dealer = true;
      }
      else{
        is_dealer = false;
      }
      if (this->players[(this->dealer+1+i)%4]->make_trump(
        upcard, is_dealer, this->round, this->trump)){
        orderer = i;
        cout << this->players[(this->dealer+1+i)%4]->get_name() 
        << " orders up " << this->trump << endl;
        if (this->round == 1){
          this->players[this->dealer]->add_and_discard(upcard);
        }
        cout << endl;
        break; 
      }
      else{
        cout << this->players[(this->dealer+1+i)%4]->get_name() 
        << " passes" << endl;
      }
    }
    if ((this->dealer+1+orderer)%4 == 0 || (this->dealer+1+orderer)%4 == 2){
      this->order_up = 13;
    }
    else if ((this->dealer+1+orderer)%4 == 1 || (this->dealer+1+orderer)%4 == 3){
      this->order_up = 24;
    }
    //cout << "trump suit: " << this->trump << endl;
    /*for(int i = 0; i< 4; i++){
      cout << "player" << i << ": " << endl;
      this->players[i]->show_cards();
    }*/
  };
  //Play five tricks
  int trick(){
    int winner = leader;
    Card lead_card = this->players[leader]->lead_card(this->trump);
    Card greatest = lead_card;
    cout << lead_card.get_rank() << " of " << lead_card.get_suit() 
    << " led by " << this->players[leader]->get_name() << endl;
    for(int i = 0; i<3; i++){
      //cout << "cards against: " << (leader+1+i)%4 << endl;
      Card played = players[(leader+1+i)%4]->play_card(lead_card, this->trump);
      cout << played.get_rank() << " of " << played.get_suit() 
      << " played by " << players[(leader+1+i)%4]->get_name() << endl;
      if(Card_less(greatest, played, lead_card, this->trump)){
        greatest = played;
        winner = (leader+1+i)%4;
      }
    }
    cout << players[winner]->get_name() << " takes the trick" << endl;
    cout << endl;
    leader = winner;
    return winner;
  };
  void trick_winner(int tw){
    if (tw == 0 || tw == 2){
      this->trick0_2++;
    }
    else if (tw == 1 || tw == 3){
      this->trick1_3++;
    } 
  };
  void hand_winner(){
    //cout << "0_2 score: " << this->trick0_2 << endl;
    //cout << "1_3 score: " << this->trick1_3 << endl;
    //cout << "order up: " << this->order_up << endl;
    if (this->trick0_2 >= 5){
      cout << this->players[0]->get_name() << " and "
      << this->players[2] -> get_name() << " win the hand" << endl;
      if(this->order_up == 13){
        cout << "march! " << endl;
      }
      else if(this->order_up == 24){
        cout << "euchred!" << endl;
      }
      this->score0_2+=2;
    }
    else if (this->trick1_3 >= 5){
      cout << this->players[1]->get_name() << " and "
      << this->players[3] -> get_name() << " win the hand" << endl;
      if(this->order_up == 24){
        cout << "march!" << endl;
      }
      else if(this->order_up == 13){
        cout << "euchred!" << endl;
      }
      this->score1_3+=2;
    }
    else if (this->trick0_2 == 3 || this->trick0_2 == 4){
      cout << this->players[0]->get_name() << " and "
       << this->players[2] -> get_name() << " win the hand" << endl;
      if(this->order_up == 13){
        this->score0_2++;
      }
      else if(this->order_up == 24){
        this->score0_2+=2;
        cout << "euchred!" << endl;
      }
    }
    else if (this->trick1_3 == 3 || this->trick1_3 == 4){
      cout << this->players[1]->get_name() << " and "
      << this->players[3] -> get_name() << " win the hand" << endl;
      if(this->order_up == 24){
        this->score1_3++;
      }
      else if(this->order_up == 13){
        cout << "euchred!" << endl;
        this->score1_3+=2;
      }
    }
  };
};


int main(int argc, char **argv) {
  // Read command line args and check for errors

  if (argc != 12){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "     
    "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "     
    "NAME4 TYPE4" << endl;
    return 1;
  }

  in_data data;
  data.shuffle = argv[2];
  data.points = stoi(argv[3]);
  data.name1 = argv[4];
  data.name2 = argv[6];
  data.name3 = argv[8];
  data.name4 = argv[10];
  data.strat1 = argv[5];
  data.strat2 = argv[7];
  data.strat3 = argv[9];
  data.strat4 = argv[11];

  if (data.points < 1 || data.points > 100){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "     
    "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "     
    "NAME4 TYPE4" << endl;
    return 1;
  }
  else if (data.shuffle != "noshuffle" && data.shuffle != "shuffle"){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "     
    "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "     
    "NAME4 TYPE4" << endl;
    return 1;
  }
  else if (
    (data.strat1 != "Simple" && data.strat1 != "Human") ||
    (data.strat2 != "Simple" && data.strat2 != "Human") ||
    (data.strat3 != "Simple" && data.strat3 != "Human") ||
    (data.strat4 != "Simple" && data.strat4 != "Human")
    ){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "     
    "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "     
    "NAME4 TYPE4" << endl;
    return 1;
  }

  for(int i = 0;i <12; i++){
    cout<< argv[i] << " ";
  }
  cout << endl;
  Game game(data);
  game.play();
}