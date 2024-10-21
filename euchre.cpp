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
    cout << "playing game" << endl;
    /*
    while (this->score1 < this->points && this->score2 < this->points){
      cout << this->hand << endl;
      trick1 = 0;
      trick2 = 0;
      if (this->shuf){
        shuffle();
      }
      deal();
      make_trump();
      for(int i = 0; i < 5; i++){
        trick();
      } 
      this->hand++;
      if (dealer >= 3){
        dealer = 0;
      }
      else{
        dealer++;
      }
    }
    cout << "game over" << endl;
    for(size_t i = 0; i < players.size(); ++i){   
      delete players[i]; 
    }*/
    deal();
    make_trump();
    for (int i = 0; i<5; i++){
      trick();
    }
  this->dealer = 0;
  this->trick1 = 0;
  this->trick2 = 0;
  this->score0_2 = 0;
  this->score1_3 = 0; 
  this->hand = 0;
  this->order_up = 0;
  }

  private:   
  std::vector<Player*> players;   
  Pack pack;   // ...
  int points;
  int dealer = 0;
  int trick1 = 0;
  int trick2 = 0;
  int score0_2 = 0;
  int score1_3 = 0; 
  int hand = 0;
  int round = 1;
  int order_up;
  bool shuf;
  Card upcard;
  Suit trump;
  //Shuffles Deck
  void shuffle(){
    cout << "shuffling deck" << endl;
    this->pack.shuffle();
  };   
  //Deals cards 
  void deal(){
    //Identify dealer
    this->dealer = 0;
    //Begin with player to the left of them
    for(int i = 0; i< 8; i++){
      if ((i%2 == 0 && i<4) || (i%2 == 1 && i>=4)){
        //cout << 3 << " ";
        this->players[(this->dealer+1+i)%4]->add_card(this->pack.deal_one());
        this->players[(this->dealer+1+i)%4]->add_card(this->pack.deal_one());
        this->players[(this->dealer+1+i)%4]->add_card(this->pack.deal_one());
      }
      else if ((i%2 == 1 && i<4) || (i%2 == 0 && i>=4)){
        //cout << 2 << " ";
        this->players[(this->dealer+1+i)%4]->add_card(this->pack.deal_one());
        this->players[(this->dealer+1+i)%4]->add_card(this->pack.deal_one());
      }
      //cout << "player: " << (dealer + 1 + i)%4 << endl; 
    }
    for(int i = 0; i< 4; i++){
      //cout << "player" << i+1 << ": " << endl;
      //this->players[i]->show_cards();
    }
  };   
  //Round to determine who gets trump
  void make_trump(){
    Card upcard = this->pack.deal_one();
    this->trump = upcard.get_suit();
    cout << "upcard: " << this->trump << endl;
    this->round = 1;
    int i = 0;
    while(!this->players[(this->dealer+1+i)%4]->make_trump(upcard, true, this->round, this->trump))
    {
      cout << (this->dealer+1+i)%4 << endl;
      if(i> 3){
        this->round= 2;
      }
      if (i>= 7){
        return;
      }
      i++;
    }
    cout << this->trump;
    if ((this->dealer+1+i)%4 == 0 || (this->dealer+1+i)%4 == 2){
      this->order_up = 02;
    }
    else if ((this->dealer+1+i)%4 == 1 || (this->dealer+1+i)%4 == 3){
      this->order_up = 13;
    }
  };
  //Play the hand of 
  void play_hand(){
    cout << "playing hand" << endl;
  };
  //Play five tricks
  void trick(){
    cout << "playing hand" << endl;
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

  Game game(data);
  game.play();
}