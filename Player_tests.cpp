#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;


TEST(test_player_insertion) {

  Player * human = Player_factory("NotRobot", "Human");
  ostringstream oss1;
  oss1 << * human;
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  Player * alice = Player_factory("Alice", "Simple");
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  Player * JOE = Player_factory("JOE", "Simple");
  ostringstream oss3;
  oss3 << *JOE;
  ASSERT_EQUAL(oss3.str(), "JOE");

  delete human;
  delete alice;
  delete JOE;
}

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    Player * ROBO = Player_factory("ROBO", "Human");
    ASSERT_EQUAL("ROBO", ROBO->get_name());

    Player * D23 = Player_factory("D23", "Simple");
    ASSERT_EQUAL("D23", D23->get_name());

    delete alice;
    delete ROBO;
    delete D23;
}

TEST(test_simple_player_make_trump) {

  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);
  delete bob;

  Player * p1 = Player_factory("p1", "Simple");
  p1->add_card(Card(NINE, SPADES));
  p1->add_card(Card(TEN, HEARTS));
  p1->add_card(Card(QUEEN, DIAMONDS));
  p1->add_card(Card(KING, CLUBS));
  p1->add_card(Card(ACE, SPADES));
  Suit trump1;
  bool orderup11 = p1->make_trump(nine_spades, true, 1, trump1);
  ASSERT_FALSE(orderup11);
  bool orderup12 = p1->make_trump(nine_spades, true, 2, trump1);
  ASSERT_TRUE(orderup12);
  ASSERT_EQUAL(trump1, CLUBS);
  delete p1;


  Player * p2 = Player_factory("p2", "Simple");
  p2->add_card(Card(NINE, DIAMONDS));
  p2->add_card(Card(TEN, HEARTS));
  p2->add_card(Card(QUEEN, DIAMONDS));
  p2->add_card(Card(JACK, CLUBS));
  p2->add_card(Card(ACE, SPADES));
  Suit trump2;
  bool orderup21 = p2->make_trump(nine_spades, true, 1, trump2);
  ASSERT_TRUE(orderup21);
  ASSERT_EQUAL(trump2, SPADES);
  bool orderup22 = p2->make_trump(nine_spades, true, 2, trump2);
  ASSERT_TRUE(orderup22);
  ASSERT_EQUAL(trump2, CLUBS);
  delete p2;

  Player * p3 = Player_factory("p3", "Simple");
  p3->add_card(Card(TEN, CLUBS));
  p3->add_card(Card(JACK, SPADES));
  p3->add_card(Card(QUEEN, HEARTS));
  p3->add_card(Card(JACK, DIAMONDS));
  p3->add_card(Card(ACE, SPADES));
  Card ten_hearts(TEN, HEARTS);
  Suit trump3;
  bool orderup31 = p3->make_trump(ten_hearts, true, 1, trump3);
  ASSERT_TRUE(orderup31);
  ASSERT_EQUAL(trump3, HEARTS);
  bool orderup32 = p3->make_trump(ten_hearts, true, 2, trump3);
  ASSERT_TRUE(orderup32);
  delete p3;

  Player * p4 = Player_factory("p4", "Simple");
  p4->add_card(Card(TEN, CLUBS));
  p4->add_card(Card(JACK, SPADES));
  p4->add_card(Card(QUEEN, HEARTS));
  p4->add_card(Card(JACK, CLUBS));
  p4->add_card(Card(ACE, SPADES));
  Suit trump4;
  bool orderup41 = p4->make_trump(ten_hearts, true, 1, trump4);
  ASSERT_FALSE(orderup41);
  bool orderup42 = p4->make_trump(ten_hearts, false, 2, trump4);
  ASSERT_FALSE(orderup42);
  bool orderup43 = p4->make_trump(ten_hearts, true, 2, trump4);
  ASSERT_TRUE(orderup43);
  delete p4;

  Player * p5 = Player_factory("p5", "Simple");
  p5->add_card(Card(TEN, CLUBS));
  p5->add_card(Card(JACK, DIAMONDS));
  p5->add_card(Card(QUEEN, HEARTS));
  p5->add_card(Card(JACK, CLUBS));
  p5->add_card(Card(ACE, SPADES));
  Card jack_hearts(JACK, HEARTS);
  Suit trump5;
  bool orderup5 = p5->make_trump(jack_hearts, false, 1, trump5);
  ASSERT_TRUE(orderup5);
  ASSERT_EQUAL(trump5, HEARTS);
  delete p5;

  Player * p6 = Player_factory("p6", "Simple");
  p6->add_card(Card(TEN, CLUBS));
  p6->add_card(Card(TEN, DIAMONDS));
  p6->add_card(Card(NINE, HEARTS));
  p6->add_card(Card(TEN, HEARTS));
  p6->add_card(Card(JACK, DIAMONDS));
  Suit trump6;
  bool orderup61 = p6->make_trump(jack_hearts, false, 1, trump6);
  ASSERT_FALSE(orderup61);
  bool orderup62 = p6->make_trump(jack_hearts, false, 2, trump6);
  ASSERT_TRUE(orderup62);
  ASSERT_EQUAL(trump6, DIAMONDS);
  bool orderup63 = p6->make_trump(jack_hearts, true, 2, trump6);
  ASSERT_TRUE(orderup63);
  ASSERT_EQUAL(trump6, DIAMONDS);
  delete p6;

  Player * p7 = Player_factory("p7", "Simple");
  p7->add_card(Card(TEN, CLUBS));
  p7->add_card(Card(NINE, CLUBS));
  p7->add_card(Card(NINE, SPADES));
  p7->add_card(Card(TEN, SPADES));
  p7->add_card(Card(JACK, DIAMONDS));
  Suit trump7;
  bool orderup7 = p7->make_trump(jack_hearts, false, 2, trump7);
  ASSERT_TRUE(orderup7);
  ASSERT_EQUAL(trump7, DIAMONDS);
  delete p7;

  Player * p8 = Player_factory("p8", "Simple");
  p8->add_card(Card(TEN, CLUBS));
  p8->add_card(Card(NINE, CLUBS));
  p8->add_card(Card(NINE, SPADES));
  p8->add_card(Card(JACK, HEARTS));
  p8->add_card(Card(JACK, DIAMONDS));
  Suit trump8;
  bool orderup81 = p8->make_trump(ten_hearts, false, 1, trump8);
  ASSERT_TRUE(orderup81);
  ASSERT_EQUAL(trump8, HEARTS);
  bool orderup82 = p8->make_trump(ten_hearts, false, 2, trump8);
  ASSERT_TRUE(orderup82);
  ASSERT_EQUAL(trump8, DIAMONDS);
  bool orderup83 = p8->make_trump(ten_hearts, true, 2, trump8);
  ASSERT_TRUE(orderup83);
  ASSERT_EQUAL(trump8, DIAMONDS);
  delete p8;

  Player * p9 = Player_factory("p9", "Simple");
  p9->add_card(Card(TEN, CLUBS));
  p9->add_card(Card(NINE, CLUBS));
  p9->add_card(Card(NINE, SPADES));
  p9->add_card(Card(NINE, HEARTS));
  p9->add_card(Card(TEN, DIAMONDS));
  Suit trump9;
  bool orderup91 = p9->make_trump(ten_hearts, false, 1, trump9);
  ASSERT_FALSE(orderup91);
  bool orderup92 = p9->make_trump(ten_hearts, false, 2, trump9);
  ASSERT_FALSE(orderup92);
  bool orderup93 = p9->make_trump(ten_hearts, true, 2, trump9);
  ASSERT_TRUE(orderup93);
  ASSERT_EQUAL(trump9, DIAMONDS);
  delete p9;

}


TEST(add_and_discard){

  Player * p1 = Player_factory("p1", "Simple");
  p1->add_card(Card(NINE, SPADES));
  p1->add_card(Card(TEN, SPADES));
  p1->add_card(Card(QUEEN, SPADES));
  p1->add_card(Card(KING, SPADES));
  p1->add_card(Card(ACE, SPADES));
  p1->add_and_discard(Card(NINE, HEARTS));
  Card card_led1 = p1->lead_card(SPADES);
  Card nine_hearts(NINE, HEARTS);
  ASSERT_EQUAL(card_led1, nine_hearts); //check led card
  delete p1;

  Player * p2 = Player_factory("p2", "Simple");
  p2->add_card(Card(KING, SPADES));
  p2->add_card(Card(ACE, SPADES));
  p2->add_card(Card(QUEEN, SPADES));
  p2->add_card(Card(JACK, CLUBS));
  p2->add_card(Card(JACK, SPADES));
  p2->add_and_discard(Card(QUEEN, HEARTS));
  Card card_led21 = p2->lead_card(DIAMONDS);
  Card ace_spades(ACE, SPADES);
  Card queen_hearts(QUEEN, HEARTS);
  ASSERT_EQUAL(card_led21, ace_spades); //check led card
  Card card_led22 = p2->lead_card(CLUBS);
  ASSERT_EQUAL(card_led22, ace_spades); //check led card
  Card card_led23 = p2->lead_card(SPADES);
  ASSERT_EQUAL(card_led23, queen_hearts); //check led card
  delete p2;


  Player * p3 = Player_factory("p3", "Simple");
  p3->add_card(Card(KING, CLUBS));
  p3->add_card(Card(ACE, CLUBS));
  p3->add_card(Card(QUEEN, CLUBS));
  p3->add_card(Card(TEN, CLUBS));
  p3->add_card(Card(NINE, CLUBS));
  p3->add_and_discard(Card(NINE, SPADES));
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played31=p3->play_card(nine_diamonds,HEARTS); 
  ASSERT_EQUAL(card_played31, Card(NINE, SPADES));
  delete p3;


  Player * p4 = Player_factory("p4", "Simple");
  p4->add_card(Card(KING, CLUBS));
  p4->add_card(Card(ACE, CLUBS));
  p4->add_card(Card(QUEEN, CLUBS));
  p4->add_card(Card(JACK, CLUBS));
  p4->add_card(Card(TEN, CLUBS));
  p4->add_and_discard(Card(NINE, CLUBS));
  Card nine_spades(NINE, SPADES);
  Card card_played41=p4->play_card(nine_spades,HEARTS); 
  ASSERT_EQUAL(card_played41, Card(TEN, CLUBS));
  delete p4;

}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));
  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card
  delete bob;


  Player * p1 = Player_factory("p1", "Simple");
  p1->add_card(Card(NINE, HEARTS));
  p1->add_card(Card(TEN, SPADES));
  p1->add_card(Card(QUEEN, CLUBS));
  p1->add_card(Card(KING, SPADES));
  p1->add_card(Card(ACE, DIAMONDS));
  p1->add_and_discard(Card(ACE, CLUBS));
  Card card_led2 = p1->lead_card(CLUBS);
  Card ace_diamonds(ACE, DIAMONDS);
  ASSERT_EQUAL(card_led2, ace_diamonds);
  delete p1;

  Player * p2 = Player_factory("p2", "Simple");
  p2->add_card(Card(NINE, HEARTS));
  p2->add_card(Card(TEN, SPADES));
  p2->add_card(Card(QUEEN, CLUBS));
  p2->add_card(Card(KING, SPADES));
  p2->add_card(Card(ACE, CLUBS));
  Card card_led3 = p2->lead_card(CLUBS);
  Card king_spades(KING, SPADES);
  ASSERT_EQUAL(card_led3, king_spades); 
  delete p2;

  Player * p3 = Player_factory("p3", "Simple");
  p3->add_card(Card(NINE, HEARTS));
  p3->add_card(Card(TEN, SPADES));
  p3->add_card(Card(QUEEN, SPADES));
  p3->add_card(Card(KING, SPADES));
  p3->add_card(Card(ACE, DIAMONDS));
  Card card_led4 = p3->lead_card(SPADES);
  ASSERT_EQUAL(card_led4, ace_diamonds); 
  delete p3;

Player * p4 = Player_factory("p4", "Simple");
  p4->add_card(Card(NINE, HEARTS));
  p4->add_card(Card(TEN, HEARTS));
  p4->add_card(Card(QUEEN, HEARTS));
  p4->add_card(Card(KING, HEARTS));
  p4->add_card(Card(ACE, HEARTS));
  Card card_led5 = p4->lead_card(HEARTS);
  Card ace_hearts(ACE, HEARTS);
  ASSERT_EQUAL(card_led5, ace_hearts); 
  delete p4;

  Player * p5 = Player_factory("p5", "Simple");
  p5->add_card(Card(NINE, HEARTS));
  p5->add_card(Card(TEN, HEARTS));
  p5->add_card(Card(QUEEN, HEARTS));
  p5->add_card(Card(KING, HEARTS));
  p5->add_card(Card(ACE, HEARTS));
  Card card_led6 = p5->lead_card(CLUBS);
  ASSERT_EQUAL(card_led6, ace_hearts); 
  delete p5;

  Player * p6 = Player_factory("p6", "Simple");
  p6->add_card(Card(NINE, HEARTS));
  p6->add_card(Card(TEN, SPADES));
  p6->add_card(Card(QUEEN, SPADES));
  p6->add_card(Card(KING, SPADES));
  p6->add_card(Card(ACE, SPADES));
  Card card_led7 = p6->lead_card(SPADES);
  Card nine_hearts(NINE, HEARTS);
  ASSERT_EQUAL(card_led7, nine_hearts); 
  delete p6;

  Player * p7 = Player_factory("p7", "Simple");
  p7->add_card(Card(NINE, HEARTS));
  p7->add_card(Card(TEN, SPADES));
  p7->add_card(Card(ACE, CLUBS));
  p7->add_card(Card(JACK, CLUBS));
  p7->add_card(Card(JACK, SPADES));
  Card card_led8 = p7->lead_card(SPADES);
  Card ace_clubs(ACE, CLUBS);
  ASSERT_EQUAL(card_led8, ace_clubs); 
  delete p7;

  Player * p8 = Player_factory("p8", "Simple");
  p8->add_card(Card(JACK, CLUBS));
  p8->add_card(Card(QUEEN, CLUBS));
  p8->add_card(Card(KING, CLUBS));
  p8->add_card(Card(ACE, CLUBS));
  p8->add_card(Card(JACK, CLUBS));
  Card card_led9 = p8->lead_card(CLUBS);
  Card jack_clubs(JACK, CLUBS);
  ASSERT_EQUAL(card_led9, jack_clubs); 
  delete p8;


  Player * p9 = Player_factory("p9", "Simple");
  p9->add_card(Card(TEN, CLUBS));
  p9->add_card(Card(QUEEN, CLUBS));
  p9->add_card(Card(KING, CLUBS));
  p9->add_card(Card(ACE, CLUBS));
  p9->add_card(Card(JACK, SPADES));
  Card card_led10 = p9->lead_card(CLUBS);
  Card jack_spades(JACK, SPADES);
  ASSERT_EQUAL(card_led10, jack_spades); 
  delete p9;
}

TEST(test_simple_player_play_card) {

  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(nine_diamonds,HEARTS); 
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;

  Player * p1 = Player_factory("p1", "Simple");
  p1->add_card(Card(NINE, SPADES));
  p1->add_card(Card(TEN, SPADES));
  p1->add_card(Card(QUEEN, SPADES));
  p1->add_card(Card(KING, SPADES));
  p1->add_card(Card(ACE, SPADES));
  Card nine_spades(NINE, SPADES);
  Card card_played2 = p1->play_card(nine_spades, SPADES); 
  ASSERT_EQUAL(card_played2, Card(ACE, SPADES));
  delete p1;

  Player * p2 = Player_factory("p2", "Simple");
  p2->add_card(Card(NINE, SPADES));
  p2->add_card(Card(TEN, SPADES));
  p2->add_card(Card(QUEEN, SPADES));
  p2->add_card(Card(JACK, CLUBS));
  p2->add_card(Card(JACK, SPADES));
  Card cardplayed3 = p2->play_card(nine_spades, SPADES); 
  ASSERT_EQUAL(cardplayed3, Card(JACK, SPADES));
  delete p2;
  
  Player * p25 = Player_factory("p2", "Simple");
  p25->add_card(Card(NINE, SPADES));
  p25->add_card(Card(TEN, SPADES));
  p25->add_card(Card(QUEEN, SPADES));
  p25->add_card(Card(ACE, SPADES));
  p25->add_card(Card(JACK, CLUBS));
  Card cardplayed25 = p25->play_card(nine_spades, SPADES); //ERROR HERE
  ASSERT_EQUAL(cardplayed25, Card(JACK, CLUBS));
  delete p25;

  Player * p26 = Player_factory("p2", "Simple");
  p26->add_card(Card(NINE, SPADES));
  p26->add_card(Card(TEN, SPADES));
  p26->add_card(Card(QUEEN, SPADES));
  p26->add_card(Card(ACE, SPADES));
  p26->add_card(Card(JACK, CLUBS));
  Card cardplayed26 = p26->play_card(nine_spades, HEARTS); 
  ASSERT_EQUAL(cardplayed26, Card(ACE, SPADES));
  delete p26;

  Player * p3 = Player_factory("p3", "Simple");
  p3->add_card(Card(NINE, SPADES));
  p3->add_card(Card(TEN, SPADES));
  p3->add_card(Card(QUEEN, DIAMONDS));
  p3->add_card(Card(JACK, HEARTS));
  p3->add_card(Card(JACK, DIAMONDS));
  Card king_diamonds(KING, DIAMONDS);
  Card cardplayed4 = p3->play_card(king_diamonds, CLUBS); 
  ASSERT_EQUAL(cardplayed4, Card(QUEEN, DIAMONDS));
  delete p3;

  Player * p4 = Player_factory("p4", "Simple");
  p4->add_card(Card(NINE, HEARTS));
  p4->add_card(Card(TEN, SPADES));
  p4->add_card(Card(QUEEN, SPADES));
  p4->add_card(Card(KING, SPADES));
  p4->add_card(Card(KING, HEARTS));
  Card cardplayed5 = p4->play_card(king_diamonds, CLUBS); 
  ASSERT_EQUAL(cardplayed5, Card(NINE, HEARTS));
  delete p4;

  Player * p5 = Player_factory("p5", "Simple");
  p5->add_card(Card(NINE, DIAMONDS));
  p5->add_card(Card(TEN, DIAMONDS));
  p5->add_card(Card(QUEEN, DIAMONDS));
  p5->add_card(Card(KING, DIAMONDS));
  p5->add_card(Card(ACE, DIAMONDS));
  Card jack_diamonds(JACK, DIAMONDS);
  Card cardplayed6 = p5->play_card(jack_diamonds, HEARTS); 
  ASSERT_EQUAL(cardplayed6, Card(NINE, DIAMONDS));
  delete p5;
}

TEST_MAIN()
