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

  // Bob makes tump
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
  bool orderup15 = p1->make_trump(nine_spades, true, 1, trump1);
  ASSERT_FALSE(orderup15);

    bool orderup1 = p1->make_trump(nine_spades, true, 2, trump1);
    ASSERT_TRUE(orderup1);

  ASSERT_EQUAL(trump1, CLUBS);
  delete p1;


  Player * p2 = Player_factory("p2", "Simple");
  p2->add_card(Card(NINE, DIAMONDS));
  p2->add_card(Card(TEN, HEARTS));
  p2->add_card(Card(QUEEN, DIAMONDS));
  p2->add_card(Card(JACK, CLUBS));
  p2->add_card(Card(ACE, SPADES));

  Suit trump2;
  bool orderup2 = p2->make_trump(nine_spades, true, 1, trump2);
  ASSERT_TRUE(orderup2);
  ASSERT_EQUAL(trump2, SPADES);
  delete p2;

  Player * p3 = Player_factory("p3", "Simple");
  p3->add_card(Card(TEN, CLUBS));
  p3->add_card(Card(JACK, SPADES));
  p3->add_card(Card(QUEEN, HEARTS));
  p3->add_card(Card(JACK, DIAMONDS));
  p3->add_card(Card(ACE, SPADES));

  Card ten_hearts(TEN, HEARTS);
  Suit trump3;
  bool orderup3 = p3->make_trump(ten_hearts, true, 1, trump3);
  ASSERT_TRUE(orderup3);
  ASSERT_EQUAL(trump3, HEARTS);
  delete p3;

  Player * p4 = Player_factory("p4", "Simple");
  p4->add_card(Card(TEN, CLUBS));
  p4->add_card(Card(JACK, SPADES));
  p4->add_card(Card(QUEEN, HEARTS));
  p4->add_card(Card(JACK, CLUBS));
  p4->add_card(Card(ACE, SPADES));

  Suit trump4;
  bool orderup4 = p4->make_trump(ten_hearts, true, 1, trump4);
  ASSERT_FALSE(orderup4);
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
  bool orderup6 = p6->make_trump(jack_hearts, false, 1, trump6);
  ASSERT_FALSE(orderup6);
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
  p1->add_and_discard(
    Card(ACE, CLUBS)
  );
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
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;


  Player * p1 = Player_factory("p1", "Simple");
  p1->add_card(Card(NINE, SPADES));
  p1->add_card(Card(TEN, SPADES));
  p1->add_card(Card(QUEEN, SPADES));
  p1->add_card(Card(KING, SPADES));
  p1->add_card(Card(ACE, SPADES));

  Card card_played2 = p1->play_card(nine_diamonds, SPADES); 

  ASSERT_EQUAL(card_played2, Card(NINE, SPADES));
  delete p1;



  Player * p2 = Player_factory("p2", "Simple");
  p2->add_card(Card(NINE, SPADES));
  p2->add_card(Card(TEN, SPADES));
  p2->add_card(Card(QUEEN, SPADES));
  p2->add_card(Card(JACK, CLUBS));
  p2->add_card(Card(JACK, SPADES));

  Card cardplayed3 = p2->play_card(nine_diamonds, SPADES); 
  ASSERT_EQUAL(cardplayed3, Card(NINE, SPADES));
  delete p2;

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
  ASSERT_EQUAL(cardplayed6, Card(ACE, DIAMONDS));
  delete p5;
}

TEST_MAIN()
